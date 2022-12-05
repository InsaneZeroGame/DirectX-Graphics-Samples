#pragma once
#include <mutex>



namespace EngineCore
{
	class INocopy
	{
	public:
		INocopy() {};
		virtual ~INocopy() {};
		INocopy(INocopy&) = delete;
		INocopy(INocopy&&) = delete;
		INocopy& operator=(INocopy&) = delete;
	private:

	};

	


	template<typename T>
	class Singleton : public INocopy
	{
	public:
		virtual ~Singleton() {};

		static T& GetInstance() 
		{
			std::call_once(mOnceFlag, CreateInstance);
			return mInstance;
		}
	protected:
		Singleton() {};

		static void CreateInstance()
		{
			static T mInstance;
		}

		static T mInstance;

		static std::once_flag mOnceFlag;
	};

	template<typename T> std::once_flag Singleton<T>::mOnceFlag;
	template<typename T> T Singleton<T>::mInstance;

	
}

