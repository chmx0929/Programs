

#include "PixelBuffer.h"
#include "ColorData.h"
#include "PixelBufferStack.h"
#include <iostream>
#include <stdlib.h>
#include <string>

PixelBufferStack::PixelBufferStack(PixelBuffer* initial_buff) {
    m_bufferStack=0;
	  pushBuffer(initial_buff,PixelBufferStack::START,"");
}

PixelBufferStack::~PixelBufferStack() {
        if (m_bufferStack->next) {
            destroyDownBufferStack(&m_bufferStack->next);
        }
        destroyUpBufferStack(&m_bufferStack);
}

void PixelBufferStack::pushBuffer(PixelBuffer* currentBuffer, const PixelBufferStack::Action last_action, const std::string file_name) {
    struct node* temp_node = new node();
    temp_node->saved_buffer= new PixelBuffer(currentBuffer->getWidth(),currentBuffer->getHeight(),currentBuffer->getBackgroundColor());
    PixelBuffer::copyPixelBuffer(currentBuffer,temp_node->saved_buffer);
    if(m_bufferStack) {
        temp_node->action_code = last_action;
        temp_node->file_name = file_name;
        temp_node->previous=m_bufferStack;
        if(m_bufferStack->next) {
            destroyDownBufferStack(&(m_bufferStack)->next);
        }
        m_bufferStack->next=temp_node;
    }
    m_bufferStack=temp_node;
}

PixelBufferStack::Action PixelBufferStack::getCurrentLastAction() {
    return m_bufferStack->action_code;
}

std::string PixelBufferStack::getCurrentFileName() {
    return m_bufferStack->file_name;
}


void PixelBufferStack::destroyUpBufferStack(struct node **head_ref) {
    struct node* current_node = *head_ref;
    struct node* higher_node;
    while(current_node)
    {
        higher_node=current_node->previous;
        delete current_node->saved_buffer;
        delete current_node;
        current_node=higher_node;
    }
    *head_ref=NULL;
}
void PixelBufferStack::destroyDownBufferStack(struct node **head_ref) {
    struct node* current_node = (*head_ref);
    struct node* lower_node;
    while(current_node)
    {
        lower_node=current_node->next;
        delete current_node->saved_buffer;
        delete current_node;
        current_node=lower_node;
    }
}


void PixelBufferStack::climbStack() {
	if(m_bufferStack->previous) {
        m_bufferStack=m_bufferStack->previous;
    }
}

void PixelBufferStack::descendStack(){
		if(m_bufferStack->next) {
        m_bufferStack=m_bufferStack->next;
    }
}

int PixelBufferStack::checkUpStack() {
	if(m_bufferStack->previous) {
        return 1;
    }
    else {
    	return 0;
    }
}

int PixelBufferStack::checkDownStack(){
	if(m_bufferStack->next) {
        return 1;
    }
    else {
    	return 0;
    }
}

PixelBuffer* PixelBufferStack::getCurrentBuffer() {
	return m_bufferStack->saved_buffer;
}
