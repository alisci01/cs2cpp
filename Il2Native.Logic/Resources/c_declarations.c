// interface cast
template <typename C, typename T> 
inline typename std::enable_if<!is_value_type<T>::value, C>::type interface_cast (T t)
{
	if (t == nullptr)
	{
		return nullptr;
	}

	return t->operator C();
}

template <typename C, typename T> 
inline typename std::enable_if<is_value_type<T>::value, C>::type interface_cast (T t)
{
	return t->operator C();
}

template <typename C, typename T> 
inline typename std::enable_if<!is_interface_type<T>::value, C>::type dynamic_interface_cast (T t)
{
	if (t == nullptr)
	{
		return nullptr;
	}

	return reinterpret_cast<C>(t->__get_interface(&std::remove_pointer<C>::type::__type));
}

template <typename C, typename T> 
inline typename std::enable_if<is_interface_type<T>::value, C>::type dynamic_interface_cast (T t)
{
	if (t == nullptr)
	{
		return nullptr;
	}

	return reinterpret_cast<C>(object_cast(t)->__get_interface(&std::remove_pointer<C>::type::__type));
}

// Boxing internals
template <typename T> inline typename std::enable_if<is_struct_type<T>::value, T>::type* __box (T t)
{
	return new T(t);
}

template <typename T, typename _CLASS = typename valuetype_to_class<T>::type> inline typename std::enable_if<is_value_type<T>::value && !is_struct_type<T>::value && !is_interface_type<T>::value, _CLASS>::type* __box (T t)
{
	return __new<_CLASS>(t);
}

template <typename T> inline typename std::enable_if<!is_value_type<T>::value && !is_interface_type<T>::value, T>::type __box (T t)
{
	return t;
}

template <typename T> inline typename std::enable_if<is_interface_type<T>::value, object*>::type __box (T t)
{
	return object_cast(t);
}

// Unboxing internals
template <typename T> 
inline T __unbox(T* t)
{
	return *t;
}

template <typename T> 
inline typename std::enable_if<is_class_type<T>::value, T>::type __unbox(object* o)
{
	return cast<T>(o);
}

template <typename T, typename _CLASS = typename valuetype_to_class<T>::type, typename _VAL = typename class_to_valuetype<T>::type> 
inline typename std::enable_if<is_value_type<T>::value, _VAL>::type __unbox(object* o)
{
	return *cast<_CLASS*>(o);
}

template <typename T> 
inline typename std::enable_if<is_interface_type<T>::value, T>::type __unbox(T t)
{
	return t;
}

template <typename T> 
inline typename std::enable_if<is_interface_type<T>::value, T>::type __unbox(object* o)
{
	return dynamic_interface_cast<T>(o);
}

// cast internals
template <typename D, typename S> 
inline typename std::enable_if<is_class_type<D>::value && is_class_type<S>::value, D>::type as(S s)
{
	return dynamic_cast<D>(s);
}

template <typename D, typename S> 
inline typename std::enable_if<is_value_type<D>::value || is_value_type<S>::value, D>::type as(S s)
{
	return nullptr;
}

// special case for interfaces
// add flag to each interface to be able to create is_interface<T>::value
template <typename D, typename S> 
inline typename std::enable_if<is_interface_type<D>::value && is_class_type<S>::value, D>::type as(S s)
{
	return dynamic_interface_cast<D>(s);
}

template <typename D, typename S> 
inline typename std::enable_if<is_class_type<D>::value && is_interface_type<S>::value, D>::type as(S s)
{
	return dynamic_cast<D>(object_cast(s));
}

template <typename D, typename S> 
inline typename std::enable_if<is_interface_type<D>::value && is_interface_type<S>::value, D>::type as(S s)
{
	return dynamic_interface_cast<D>(object_cast(s));
}

// cast internals
template <typename D, typename S> 
inline typename std::enable_if<is_class_type<D>::value && is_class_type<S>::value, bool>::type is(S s)
{
	return dynamic_cast<D>(s) != nullptr;
}

template <typename D, typename S> 
inline typename std::enable_if<is_value_type<D>::value || is_value_type<S>::value, bool>::type is(S s)
{
	return false;
}

// special case for interfaces
// add flag to each interface to be able to create is_interface<T>::value
template <typename D, typename S> 
inline typename std::enable_if<is_interface_type<D>::value && is_class_type<S>::value, bool>::type is(S s)
{
	return dynamic_interface_cast<D>(s) != nullptr;
}

template <typename D, typename S> 
inline typename std::enable_if<is_class_type<D>::value && is_interface_type<S>::value, bool>::type is(S s)
{
	return dynamic_cast<D>(object_cast(s)) != nullptr;
}

template <typename D, typename S> 
inline typename std::enable_if<is_interface_type<D>::value && is_interface_type<S>::value, bool>::type is(S s)
{
	return dynamic_interface_cast<D>(object_cast(s)) != nullptr;
}

// Constrained internals (for templates)
template <typename D, typename S> 
inline typename std::enable_if<std::is_same<D, S>::value, D>::type constrained (S s)
{
	return s;
}

template <typename D, typename S> 
inline typename std::enable_if<is_class_type<S>::value && !std::is_same<D, S>::value, D>::type constrained (S s)
{
	return static_cast<D>(s);
}

template <typename D, typename S> 
inline typename std::enable_if<is_interface_type<D>::value, D>::type constrained (S s)
{
	return interface_cast<D>(s);
}

template <typename D, typename S> 
inline typename std::enable_if<is_value_type<S>::value && is_class_type<D>::value, D>::type constrained (S s)
{
	return __box(s);
}

template <typename D, typename S> 
inline typename std::enable_if<is_interface_type<S>::value && is_class_type<D>::value && !is_object<D>::value, D>::type constrained (S s)
{
	return cast<D>(object_cast(s));
}

template <typename D, typename S> 
inline typename std::enable_if<is_interface_type<S>::value && is_class_type<D>::value && is_object<D>::value, D>::type constrained (S s)
{
	return object_cast(s);
}

// Typeof internals
template <typename T> inline CoreLib::System::Type* _typeof()
{
	typedef typename valuetype_to_class<typename std::remove_pointer<T>::type>::type _T;
	return &_T::__type;
}

// Decimals
int32_t DecAddSub(int32_t* d1, int32_t* d2, int32_t* res, uint8_t bSign);
int32_t DecCmp(int32_t* d1, int32_t* d2);
int32_t DecFromR4(float fltIn, int32_t* pdec);
int32_t DecFromR8(double dblIn, int32_t* pdec);
int32_t DecMul(int32_t* d1, int32_t* d2, int32_t* res);
int32_t DecDiv(int32_t* d1, int32_t* d2, int32_t* res);

// Finally block
class Finally
{
public:
	std::function<void()> _dtor;
	Finally(std::function<void()> dtor) : _dtor(dtor) {};
	~Finally() { _dtor(); }
};

// Default
template <typename T> 
inline typename std::enable_if<std::is_pointer<T>::value, T>::type __default()
{
	return nullptr;
}

template <typename T> 
inline typename std::enable_if<is_struct_type<T>::value, T>::type __default()
{
	return __init<T>();
}

template <typename T> 
inline typename std::enable_if<is_primitive_type<T>::value, T>::type __default()
{
	return T();
}

template <typename T> 
inline typename std::enable_if<std::is_void<T>::value, T>::type __default()
{
	return;
}

// Activator
template <typename T> 
typename std::enable_if<is_class_type<T>::value, T>::type __create_instance()
{
	typedef typename std::remove_pointer<T>::type _T;
	return __new<_T>();
}

template <typename T> 
T __create_instance()
{
	return __init<T>();
}

// Arrays internals
template <typename T> class __array : public CoreLib::System::Array
{
public:
	int32_t _length;
	T _data[0];

	typedef CoreLib::System::Array base;
	__array(int32_t length) { _length = length; }
	__array(const __array<T>&) = delete;
	__array(__array<T>&&) = delete;

	static __array<T>* __new_array(int32_t length)
	{
		auto size = sizeof(__array<T>) + length * sizeof(T);
		return new ((int32_t)size, is_primitive_type<T>::value) __array<T>(length);
	}

	template <typename... Ta> static __array<T>* __new_array_init(Ta... items)
	{
		auto count = sizeof...(items);
		auto data_size = count * sizeof(T);
		auto size = sizeof(__array<T>) + data_size;
		auto instance = new ((int32_t)size, is_primitive_type<T>::value) __array<T>(count);

		// initialize
		T tmp[] = {items...};
		memcpy(&instance->_data[0], &tmp, data_size);

		return instance;
	}

	inline const T operator [](int32_t index) const 
	{ 
		if (index < 0 || index > _length)
		{
			throw __new<CoreLib::System::IndexOutOfRangeException>();
		}

		return _data[index]; 
	}

	inline T& operator [](int32_t index) 
	{
		if (index < 0 || index > _length)
		{
			throw __new<CoreLib::System::IndexOutOfRangeException>();
		}

		return _data[index]; 
	}

	inline operator int32_t() const { return (size_t)_length; }

	// Array
	virtual int32_t __array_element_size() override;
	virtual void InternalGetReference(void*, int32_t, int32_t*) override;
	virtual int32_t get_Length() override;
	virtual int32_t get_Rank() override;

	// IListT1
	T System_Collections_Generic_IListT1_get_Item(int32_t);
	void System_Collections_Generic_IListT1_set_Item(int32_t, T);
	int32_t System_Collections_Generic_IListT1_IndexOf(T);
	void System_Collections_Generic_IListT1_Insert(int32_t, T);
	void System_Collections_Generic_IListT1_RemoveAt(int32_t);

	// ICollectionT1
	int32_t System_Collections_Generic_ICollectionT1_get_Count();
	bool System_Collections_Generic_ICollectionT1_get_IsReadOnly();
	void System_Collections_Generic_ICollectionT1_Add(T);
	void System_Collections_Generic_ICollectionT1_Clear(); 
	bool System_Collections_Generic_ICollectionT1_Contains(T);
	void System_Collections_Generic_ICollectionT1_CopyTo(__array<T>*, int32_t);
	bool System_Collections_Generic_ICollectionT1_Remove(T);

	// IEnumerableT1
	CoreLib::System::Collections::Generic::IEnumeratorT1<T>* System_Collections_Generic_IEnumerableT1_GetEnumerator();

	// IList
	CoreLib::System::Object* System_Collections_IList_get_Item(int32_t);
	void System_Collections_IList_set_Item(int32_t, CoreLib::System::Object*);
	int32_t System_Collections_IList_Add(CoreLib::System::Object*);
	bool System_Collections_IList_Contains(CoreLib::System::Object*);
	void System_Collections_IList_Clear();
	bool System_Collections_IList_get_IsReadOnly();
	bool System_Collections_IList_get_IsFixedSize(); 
	int32_t System_Collections_IList_IndexOf(CoreLib::System::Object*);
	void System_Collections_IList_Insert(int32_t, CoreLib::System::Object*);
	void System_Collections_IList_Remove(CoreLib::System::Object*);
	void System_Collections_IList_RemoveAt(int32_t);

	// ICollection
	void System_Collections_ICollection_CopyTo(CoreLib::System::Array*, int32_t);
	int32_t System_Collections_ICollection_get_Count();
	CoreLib::System::Object* System_Collections_ICollection_get_SyncRoot();
	bool System_Collections_ICollection_get_IsSynchronized();

	// IEnumerable
	CoreLib::System::Collections::IEnumerator* System_Collections_IEnumerable_GetEnumerator();

	class __array_IListT1 : public virtual CoreLib::System::Collections::Generic::IListT1<T>
	{
	public:
		__array_IListT1(__array<T>* class_) : _class{class_} {}
		operator object*()
		{
			return this->_class;
		}
		__array<T>* _class;
		T System_Collections_Generic_IListT1_get_Item(int32_t);
		void System_Collections_Generic_IListT1_set_Item(int32_t, T);
		int32_t System_Collections_Generic_IListT1_IndexOf(T);
		void System_Collections_Generic_IListT1_Insert(int32_t, T);
		void System_Collections_Generic_IListT1_RemoveAt(int32_t);
		int32_t System_Collections_Generic_ICollectionT1_get_Count();
		bool System_Collections_Generic_ICollectionT1_get_IsReadOnly();
		void System_Collections_Generic_ICollectionT1_Add(T);
		void System_Collections_Generic_ICollectionT1_Clear();
		bool System_Collections_Generic_ICollectionT1_Contains(T);
		void System_Collections_Generic_ICollectionT1_CopyTo(__array<T>*, int32_t);
		bool System_Collections_Generic_ICollectionT1_Remove(T);
		CoreLib::System::Collections::Generic::IEnumeratorT1<T>* System_Collections_Generic_IEnumerableT1_GetEnumerator();
		CoreLib::System::Collections::IEnumerator* System_Collections_IEnumerable_GetEnumerator();
	};
	operator CoreLib::System::Collections::Generic::IListT1<T>*()
	{
		return new __array_IListT1(this);
	}
	class __array_ICollectionT1 : public virtual CoreLib::System::Collections::Generic::ICollectionT1<T>
	{
	public:
		__array_ICollectionT1(__array<T>* class_) : _class{class_} {}
		operator object*()
		{
			return this->_class;
		}
		__array<T>* _class;
		int32_t System_Collections_Generic_ICollectionT1_get_Count();
		bool System_Collections_Generic_ICollectionT1_get_IsReadOnly();
		void System_Collections_Generic_ICollectionT1_Add(T);
		void System_Collections_Generic_ICollectionT1_Clear();
		bool System_Collections_Generic_ICollectionT1_Contains(T);
		void System_Collections_Generic_ICollectionT1_CopyTo(__array<T>*, int32_t);
		bool System_Collections_Generic_ICollectionT1_Remove(T);
		CoreLib::System::Collections::Generic::IEnumeratorT1<T>* System_Collections_Generic_IEnumerableT1_GetEnumerator();
		CoreLib::System::Collections::IEnumerator* System_Collections_IEnumerable_GetEnumerator();
	};
	operator CoreLib::System::Collections::Generic::ICollectionT1<T>*()
	{
		return new __array_ICollectionT1(this);
	}
	class __array_IEnumerableT1 : public virtual CoreLib::System::Collections::Generic::IEnumerableT1<T>
	{
	public:
		__array_IEnumerableT1(__array<T>* class_) : _class{class_} {}
		operator object*()
		{
			return this->_class;
		}
		__array<T>* _class;
		CoreLib::System::Collections::Generic::IEnumeratorT1<T>* System_Collections_Generic_IEnumerableT1_GetEnumerator();
		CoreLib::System::Collections::IEnumerator* System_Collections_IEnumerable_GetEnumerator();
	};
	operator CoreLib::System::Collections::Generic::IEnumerableT1<T>*()
	{
		return new __array_IEnumerableT1(this);
	}
	class __array_IEnumerable : public virtual CoreLib::System::Collections::IEnumerable
	{
	public:
		__array_IEnumerable(__array<T>* class_) : _class{class_} {}
		operator object*()
		{
			return this->_class;
		}
		__array<T>* _class;
		CoreLib::System::Collections::IEnumerator* System_Collections_IEnumerable_GetEnumerator();
	};
	operator CoreLib::System::Collections::IEnumerable*()
	{
		return new __array_IEnumerable(this);
	}
	class __array_IList : public virtual CoreLib::System::Collections::IList
	{
	public:
		__array_IList(__array<T>* class_) : _class{class_} {}
		operator object*()
		{
			return this->_class;
		}
		__array<T>* _class;
		CoreLib::System::Object* System_Collections_IList_get_Item(int32_t);
		void System_Collections_IList_set_Item(int32_t, CoreLib::System::Object*);
		int32_t System_Collections_IList_Add(CoreLib::System::Object*);
		bool System_Collections_IList_Contains(CoreLib::System::Object*);
		void System_Collections_IList_Clear();
		bool System_Collections_IList_get_IsReadOnly();
		bool System_Collections_IList_get_IsFixedSize();
		int32_t System_Collections_IList_IndexOf(CoreLib::System::Object*);
		void System_Collections_IList_Insert(int32_t, CoreLib::System::Object*);
		void System_Collections_IList_Remove(CoreLib::System::Object*);
		void System_Collections_IList_RemoveAt(int32_t);
		void System_Collections_ICollection_CopyTo(CoreLib::System::Array*, int32_t);
		int32_t System_Collections_ICollection_get_Count();
		CoreLib::System::Object* System_Collections_ICollection_get_SyncRoot();
		bool System_Collections_ICollection_get_IsSynchronized();
		CoreLib::System::Collections::IEnumerator* System_Collections_IEnumerable_GetEnumerator();
	};
	operator CoreLib::System::Collections::IList*()
	{
		return new __array_IList(this);
	}
	class __array_ICollection : public virtual CoreLib::System::Collections::ICollection
	{
	public:
		__array_ICollection(__array<T>* class_) : _class{class_} {}
		operator object*()
		{
			return this->_class;
		}
		__array<T>* _class;
		void System_Collections_ICollection_CopyTo(CoreLib::System::Array*, int32_t);
		int32_t System_Collections_ICollection_get_Count();
		CoreLib::System::Object* System_Collections_ICollection_get_SyncRoot();
		bool System_Collections_ICollection_get_IsSynchronized();
		CoreLib::System::Collections::IEnumerator* System_Collections_IEnumerable_GetEnumerator();
	};
	operator CoreLib::System::Collections::ICollection*()
	{
		return new __array_ICollection(this);
	}
};

template <typename T, int32_t RANK> class __multi_array : public CoreLib::System::Array
{
public:
	int32_t _lowerBoundries[RANK];
	int32_t _upperBoundries[RANK];
	T _data[0];

	typedef CoreLib::System::Array base;
	// TODO: finish checking boundries
	__multi_array(std::initializer_list<int32_t> boundries) : _lowerBoundries{0}
	{
		std::copy(std::begin(boundries), std::end(boundries), _upperBoundries);
	}

	const T operator [](std::initializer_list<int32_t> indexes) const 
	{ 
		auto index = 0;
		auto rank = 0;
		for (auto levelIndex : indexes)
		{
			if (rank >= RANK)
			{
				break;
			}

			if (rank == 0)
			{
				index = levelIndex;
			}
			else
			{
				auto boundryRank = rank - 1;
				auto lower = _lowerBoundries[boundryRank];
				auto upper = _upperBoundries[boundryRank];
				if (levelIndex < lower|| levelIndex > upper)
				{
					throw __new<CoreLib::System::IndexOutOfRangeException>();
				}

				index += levelIndex * (upper - lower);
			}

			rank++;
		}

		return _data[index]; 
	}

	T& operator [](std::initializer_list<int32_t> indexes) 
	{ 
		auto index = 0;
		auto rank = 0;
		for (auto levelIndex : indexes)
		{
			if (rank >= RANK)
			{
				break;
			}

			if (rank == 0)
			{
				index = levelIndex;
			}
			else
			{
				auto boundryRank = rank - 1;
				auto lower = _lowerBoundries[boundryRank];
				auto upper = _upperBoundries[boundryRank];
				if (levelIndex < lower|| levelIndex > upper)
				{
					throw __new<CoreLib::System::IndexOutOfRangeException>();
				}

				index += levelIndex * (upper - lower);
			}

			rank++;
		}

		return _data[index];  
	}

	template <typename... Ta> static __multi_array<T, RANK>* __new_array(std::initializer_list<int32_t> boundries)
	{
		auto length = std::accumulate(std::begin(boundries), std::end(boundries), 1, std::multiplies<int32_t>());
		auto size = sizeof(__multi_array<T, RANK>) + length * sizeof(T);
		return new ((int32_t)size, is_primitive_type<T>::value) __multi_array<T, RANK>(boundries);
	}

	template <typename... Ta> static __multi_array<T, RANK>* __new_array_init(std::initializer_list<int32_t> boundries, Ta... items)
	{
		auto length = std::accumulate(std::begin(boundries), std::end(boundries), 1, std::multiplies<int32_t>());
		auto size = sizeof(__multi_array<T, RANK>) + length * sizeof(T);
		auto instance = new ((int32_t)size, is_primitive_type<T>::value) __multi_array<T, RANK>(boundries);

		// initialize
		T tmp[] = {items...};
		auto data_size =  sizeof...(items) * sizeof(T);
		memcpy(&instance->_data[0], &tmp, data_size);

		return instance;
	}

	virtual int32_t __array_element_size() override;
	////virtual void InternalGetReference(void*, int32_t, int32_t*) override;
	////virtual int32_t get_Length() override;
	virtual int32_t GetUpperBound(int32_t dimension) override;
	virtual int32_t GetLowerBound(int32_t dimension) override;
	virtual int32_t GetLength(int32_t dimension) override;
	virtual int32_t get_Rank() override;
};

struct __object_extras
{
	std::timed_mutex mutex;
	std::condition_variable_any cond;
};

class __object_extras_storage
{
public:

	typedef std::unordered_map<object*, __object_extras*> map;

	__object_extras* operator[] (object* obj)
	{
		{
			std::shared_lock<std::shared_timed_mutex> lock(mutex);
			map::const_iterator got = __extras.find (obj);
			if (got != __extras.end())
			{
				return got->second;
			}
		}

		return get_or_allocate(obj);
	}

	__object_extras* get_or_allocate(object* obj)
	{
		std::unique_lock<std::shared_timed_mutex> lock(mutex);
		map::const_iterator got = __extras.find (obj);
		if (got != __extras.end())
		{
			return got->second;
		}

		auto new_object_extras = new __object_extras();
		__extras[obj] = new_object_extras;
		return new_object_extras;
	}

	void free(object* obj)
	{
		std::unique_lock<std::shared_timed_mutex> lock(mutex);
		map::const_iterator got = __extras.find (obj);
		if (got != __extras.end())
		{
			delete got->second;
			__extras.erase(got);
		}
	}

	~__object_extras_storage()
	{
		std::unique_lock<std::shared_timed_mutex> lock(mutex);
		for (auto item : __extras) 
		{
			delete item.second;
		}  
	}

	map __extras;
	mutable std::shared_timed_mutex mutex;
};

extern __object_extras_storage __object_extras_storage_instance;

class __strings_storage
{
public:

	typedef std::unordered_map<const wchar_t*, string*> map;

	string* operator() (const wchar_t* str, size_t length)
	{
		{
			std::shared_lock<std::shared_timed_mutex> lock(mutex);
			map::const_iterator got = __strings.find (str);
			if (got != __strings.end())
			{
				return got->second;
			}
		}

		return get_or_allocate(str, length);
	}

	string* get_or_allocate(const wchar_t* str, size_t length)
	{
		std::unique_lock<std::shared_timed_mutex> lock(mutex);
		map::const_iterator got = __strings.find (str);
		if (got != __strings.end())
		{
			return got->second;
		}

		auto _new_string = string::FastAllocateString(length);
		std::wcsncpy(&_new_string->m_firstChar, str, length);
		__strings[str] = _new_string;
		return _new_string;
	}

	void free(const wchar_t* str)
	{
		std::unique_lock<std::shared_timed_mutex> lock(mutex);
		map::const_iterator got = __strings.find (str);
		if (got != __strings.end())
		{
			delete got->second;
			__strings.erase(got);
		}
	}

	~__strings_storage()
	{
		std::unique_lock<std::shared_timed_mutex> lock(mutex);
		for (auto item : __strings) 
		{
			delete item.second;
		}  
	}

	map __strings;
	mutable std::shared_timed_mutex mutex;
};

extern __strings_storage __strings_storage_instance;

// String literal
inline string* operator "" _s(const wchar_t* ptr, size_t length)
{
	return __strings_storage_instance(ptr, length);
}
