#ifndef RB_MAX_CAPACITY
#define RB_MAX_CAPACITY 128
#endif

template <class T>
class RingBuffer {
public :
	RingBuffer(int _size = RB_MAX_CAPACITY);
	~RingBuffer();
	void Read(const int count);
	void Write(const T value);
	void Write(const T* array);	
	unsigned int size();
	void Expend();
	void CheckShrink();
	void Traverse();
private:
	unsigned int capacity;
	unsigned int in; // –¥÷∏’Î
	unsigned int out; // ∂¡÷∏’Î

	T *pBuffer;
};
