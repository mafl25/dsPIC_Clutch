#include "circular_buffer.h"


uint16_t buffer_count(const struct circular_buffer *buffer)
{
	return buffer->count;
}

uint16_t buffer_space(const struct circular_buffer *buffer)
{
	return BUFFER_SIZE - buffer->count;
}

bool buffer_empty(const struct circular_buffer *buffer)
{
	return (buffer->count == 0) ? true : false;
}

bool buffer_full(const struct circular_buffer *buffer)
{
	return (buffer->count == BUFFER_SIZE) ? true : false;
}

bool buffer_push(struct circular_buffer *buffer, uint8_t byte)
{
	if (buffer->count == BUFFER_SIZE)
        return false;
	
    uint8_t current_position = (buffer->position + buffer->count) 
                               & (BUFFER_SIZE - 1);
    buffer->data[current_position] = byte;
    buffer->count++;
	
	return (buffer->count == BUFFER_SIZE) ? true : false;
}

int16_t buffer_pop(struct circular_buffer *buffer)
{
    if (buffer->count <= 0) {
        return -1;
    }
    
    int16_t byte = (buffer->data[buffer->position]) & 0xFF;
    buffer->position = (buffer->position + 1) & (BUFFER_SIZE - 1);
	buffer->count--;
    
    return byte;
}

void buffer_clear(struct circular_buffer *buffer)
{
	buffer->count = 0;
}

int16_t buffer_peek(const struct circular_buffer *buffer)
{
    if (buffer->count <= 0) {
        return -1;
    }
    
    int16_t byte = (buffer->data[buffer->position]) & 0xFF;
    
    return byte;
}