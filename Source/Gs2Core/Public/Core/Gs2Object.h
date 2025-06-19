#pragma once

class GS2CORE_API FGs2Object
{
protected:
	static TOptional<FString> AsText(TSharedPtr<FJsonValue> Data);

	static TOptional<int32> IntValue(TSharedPtr<FJsonValue> Data);

	static TOptional<int64> LongValue(TSharedPtr<FJsonValue> Data);

	static TOptional<float> FloatValue(TSharedPtr<FJsonValue> Data);

	static TOptional<double> DoubleValue(TSharedPtr<FJsonValue> Data);

	static TOptional<bool> BoolValue(TSharedPtr<FJsonValue> Data);

	template <typename T>
	static TSharedPtr<T> AsModel(TSharedPtr<FJsonValue> Data)
	{
		if (!Data || Data->IsNull())
		{
			return nullptr;
		}
		return T::FromJson(Data->AsObject());
	}

	template <typename T>
	static TSharedPtr<TArray<T>> AsArray(TSharedPtr<FJsonValue> Data, TFunction<T(TSharedPtr<FJsonValue>)> Convert)
	{
		if (!Data || Data->IsNull())
		{
			return nullptr;
		}
		const auto Arr = MakeShared<TArray<T>>();
		for (auto V : Data->AsArray())
		{
			Arr->Add(Convert(V));
		}
		return nullptr;
	}
	
public:
	virtual ~FGs2Object() = default;	
};
