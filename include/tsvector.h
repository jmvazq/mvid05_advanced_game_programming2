#include <mutex>
#include <vector>
#include <ostream>

template <typename T>
class tsVector {
	private:
		std::mutex mutex_;
		std::vector<T> data_;
	public:
		tsVector() { }
		tsVector(const std::size_t size)
		{
			data_ = std::vector<T>(size);
		}
		~tsVector() { }
		// Añadir un elemento al final del vector
		void push_back(const T& v)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			data_.push_back(v);
		}
		void push_back(T&& v)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			data_.push_back(v);
		}
		// Limpiar el vector
		void clear()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			data_.clear();
		}
		// Redimensionar el vector
		void resize(size_t n)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			data_.resize(n);
		}
		// Reservar elementos
		void reserve(size_t n)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			data_.reserve(n);
		}
		// Construir e insertar elemento
		void emplace_back(T&& v)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			data_.emplace_back(v);
		}
		// Borrar elementos en un rango, por índices
		void erase(std::size_t first, std::size_t last)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			const auto firstElem = data_.begin() + first;
			const auto lastElem = data_.begin() + last;
			data_.erase(firstElem, lastElem);
		}
		// Borrar un elemento por índice
		void erase(const std::size_t idx)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			const auto elem = data_.begin() + idx;
			data_.erase(elem);
		}
		// Borrar el ultimo elemento
		void pop_back()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			data_.pop_back();
		}
		// Tamaño del vector
		size_t size()
		{
			return data_.size();
		}
		// Capacidad del vector
		size_t capacity()
		{
			return data_.capacity();
		}
		// Verifica si el vector esta vacío
		bool empty()
		{
			return data_.empty();
		}
		// Accede a un elemento
		T& operator[](size_t i)
		{
			return data_.operator[](i);
		}
		const T& operator[](size_t i) const
		{
			return data_.operator[](i);
		}
		// Accede al último elemento
		T& back()
		{
			return data_.back();
		}
		const T& back() const
		{
			return data_.back();
		}
		// TODO: Recorre el vector y ejecuta la función pasada por parámetro para cada elemento
		void foreach(std::function<void(const T&)> f) const
		{
			std::lock_guard<std::mutex> guard(mutex_);
			for (T item : data_)
			{
				f(item);
			}
		}
		void foreach(std::function<void(T&)> f)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			for (T item : data_)
			{
				f(item);
			}
		}
		// Intercambia un elemento del vector por otro valor
		void swapElement(std::size_t pos, T *other)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			std::swap(data_[pos], *other);
		}
		// Intercambia el vector entero con otro vector
		void swap(tsVector &other)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			std::swap(data_, other.data_);
		}

};
