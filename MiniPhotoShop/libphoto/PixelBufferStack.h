//
//  PixelBufferStack.h
//
//

#ifndef PIXELBUFFERSTACK_H
#define PIXELBUFFERSTACK_H

#include <stdlib.h>
#include <string>

class PixelBuffer;
class ColorData;

/**
* This class faciliates the undoing and redoing of actions to a PixelBuffer canvas.
* The class centers around a doubly linked list, which stores a PixelBuffer at each node, along with a copy of the image's file name and an enum corresponding to the
* last action performed on the canvas. This information is checked at various steps of our photo editing applications, usually when deciding whether or not a change should
* be added on to the stack.
*
* In addition to the push and get methods, methods are provided to traverse the doubly linked list, and perform clean up in the desired direction
* (in order to prevent memory leaks)
*/
class PixelBufferStack {
public:
    enum Action {START, BRUSH_APPLY, IMAGE_LOAD, APPLY_THRESHOLD, APPLY_CHANNEL, APPLY_BLUR, APPLY_SHARP,
     APPLY_MOTION_BLUR, APPLY_EDGE, APPLY_SATURATE, APPLY_QUANTIZE, APPLY_DITHER, APPLY_WALLPAPER, APPLY_CHROMAKEY };


	PixelBufferStack(PixelBuffer* initial_buff);
    virtual ~PixelBufferStack();

    /// Adds a pixelbuffer to the head of the stack, removing any others waiting to be 'redone' (aka those down the stack). Also saves what action was last done to the canvas and the file name being work on
    void pushBuffer(PixelBuffer* currentBuffer, const PixelBufferStack::Action last_action, const std::string file_name);
    PixelBufferStack::Action getCurrentLastAction();
	std::string getCurrentFileName();

    void climbStack();
    void descendStack();
    int checkUpStack();
    int checkDownStack();
    PixelBuffer* getCurrentBuffer();


private:

    ///used for undo/redo button along with saving of crucial state information
    struct node {
        PixelBuffer* saved_buffer;
        PixelBufferStack::Action action_code;
		std::string file_name;
        struct node* previous;
        struct node* next;
    };

    struct node* m_bufferStack;

    void destroyUpBufferStack(struct node **head_ref);
    void destroyDownBufferStack(struct node **head_ref);

};


#endif
