// Dear ImGui: standalone example application for OSX + Metal.
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_metal.h"
#include "ImGui/imgui_impl_osx.h"
#include "ImGui/ImGuiAll.h"

#include "Main.h"

#include "Core/Allocators.h"
#include "Core/Log.h"

id <MTLDevice> gMetalDevice;

@interface AppViewController : NSViewController<NSWindowDelegate>
@end

@interface AppViewController () <MTKViewDelegate>
@property (nonatomic, readonly) MTKView *mtkView;
@property (nonatomic, strong) id <MTLDevice> device;
@property (nonatomic, strong) id <MTLCommandQueue> commandQueue;
@end

//-----------------------------------------------------------------------------------
// AppViewController
//-----------------------------------------------------------------------------------

@implementation AppViewController

-(instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    
    Initialize();

    _device = MTLCreateSystemDefaultDevice();
    _commandQueue = [_device newCommandQueue];
    
    if (!self.device)
    {
        NSLog(@"Metal is not supported");
        abort();
    }
    
    gMetalDevice = _device;

    imguiInitialize();

    // CGFloat dpiScale = NSScreen.mainScreen.backingScaleFactor;
    imguiLoadFonts(1.0f);
    
    // Setup Renderer backend
    ImGui_ImplMetal_Init(_device);

    return self;
}

-(MTKView *)mtkView
{
    return (MTKView *)self.view;
}

-(void)loadView
{
    Settings& s = GetSettings();
    self.view = [[MTKView alloc] initWithFrame:CGRectMake(0, 0,
                                                          s.layout.windowWidth == 0 ? 1200 : s.layout.windowWidth,
                                                          s.layout.windowHeight == 0 ? 720 : s.layout.windowHeight)];
}

-(void)viewDidLoad
{
    [super viewDidLoad];

    self.mtkView.device = self.device;
    self.mtkView.delegate = self;

    ImGui_ImplOSX_Init(self.view);

    [NSApp activateIgnoringOtherApps:YES];
}

-(void)drawInMTKView:(MTKView*)view
{
    @autoreleasepool {        
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize.x = view.bounds.size.width;
        io.DisplaySize.y = view.bounds.size.height;

        CGFloat framebufferScale = view.window.screen.backingScaleFactor ?: NSScreen.mainScreen.backingScaleFactor;
        io.DisplayFramebufferScale = ImVec2(framebufferScale, framebufferScale);

        id<MTLCommandBuffer> commandBuffer = [self.commandQueue commandBuffer];

        MTLRenderPassDescriptor* renderPassDescriptor = view.currentRenderPassDescriptor;
        if (renderPassDescriptor == nil)
        {
            [commandBuffer commit];
            return;
        }

        // Start the Dear ImGui frame
        ImGui_ImplMetal_NewFrame(renderPassDescriptor);
        ImGui_ImplOSX_NewFrame(view);
        ImGui::NewFrame();
        imguiBeginFrame();

        // Our state (make them static = more or less global) as a convenience to keep the example terse.
        static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        Update();

        // Rendering
        ImGui::Render();
        ImDrawData* draw_data = ImGui::GetDrawData();

        renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        id <MTLRenderCommandEncoder> renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
        [renderEncoder pushDebugGroup:@"Dear ImGui rendering"];
        ImGui_ImplMetal_RenderDrawData(draw_data, commandBuffer, renderEncoder);
        [renderEncoder popDebugGroup];
        [renderEncoder endEncoding];

        // Present
        [commandBuffer presentDrawable:view.currentDrawable];
        [commandBuffer commit];

        // Update and Render additional Platform Windows
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
        
        memTempReset(1.0f / io.Framerate);
    }
}

-(void)mtkView:(MTKView*)view drawableSizeWillChange:(CGSize)size
{
}

- (NSSize)windowWillResize:(NSWindow *)sender toSize:(NSSize)frameSize
{
    if (frameSize.width < 500)
        frameSize.width = 500;
    if (frameSize.height < 500)
        frameSize.height = 500;
    
    GetSettings().layout.windowWidth = uint16(frameSize.width);
    GetSettings().layout.windowHeight = uint16(frameSize.height);
    
    return frameSize;
}

//-----------------------------------------------------------------------------------
// Input processing
//-----------------------------------------------------------------------------------

- (void)viewWillAppear
{
    [super viewWillAppear];
    self.view.window.delegate = self;
}

- (void)windowWillClose:(NSNotification *)notification
{
    imguiSaveState();
    
    ImGui_ImplMetal_Shutdown();
    ImGui_ImplOSX_Shutdown();
    imguiRelease();
    
    Release();
}
@end

//-----------------------------------------------------------------------------------
// AppDelegate
//-----------------------------------------------------------------------------------
@interface AppDelegate : NSObject <NSApplicationDelegate>
@property (nonatomic, strong) NSWindow *window;
@end

@implementation AppDelegate

-(BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
{
    return YES;
}

-(instancetype)init
{
    if (self = [super init])
    {
        NSViewController *rootViewController = [[AppViewController alloc] initWithNibName:nil bundle:nil];
        self.window = [[NSWindow alloc] initWithContentRect:NSZeroRect
                                                  styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable | NSWindowStyleMaskMiniaturizable
                                                    backing:NSBackingStoreBuffered
                                                      defer:NO];
        self.window.contentViewController = rootViewController;
        [self.window center];
        [self.window makeKeyAndOrderFront:self];
    }
    return self;
}

@end

void* CreateRGBATexture(uint32 width, uint32 height, const void* data)
{
    MTLTextureDescriptor* textureDescriptor = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:MTLPixelFormatRGBA8Unorm
                                                                                            width:(NSUInteger)width
                                                                                            height:(NSUInteger)height
                                                                                            mipmapped:NO];
    textureDescriptor.usage = MTLTextureUsageShaderRead;
    textureDescriptor.storageMode = MTLStorageModeManaged;
    id <MTLTexture> texture = [gMetalDevice newTextureWithDescriptor:textureDescriptor];
    [texture replaceRegion:MTLRegionMake2D(0, 0, (NSUInteger)width, (NSUInteger)height) mipmapLevel:0 withBytes:data bytesPerRow:(NSUInteger)width * 4];
    return (__bridge void*)texture;
}

void DestroyTexture(void*)
{
}

// TODO:
bool SetClipboardString(const char* text)
{
    return false;
}

bool GetClipboardString(char* textOut, uint32 textSize)
{
    return false;
}


//-----------------------------------------------------------------------------------
// Application main() function
//-----------------------------------------------------------------------------------

int main(int argc, const char * argv[])
{
    return NSApplicationMain(argc, argv);
}
