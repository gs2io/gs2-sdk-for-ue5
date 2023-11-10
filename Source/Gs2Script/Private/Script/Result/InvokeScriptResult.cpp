/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include "Script/Result/InvokeScriptResult.h"

namespace Gs2::Script::Result
{
    FInvokeScriptResult::FInvokeScriptResult():
        CodeValue(TOptional<int32>()),
        ResultValue(TOptional<FString>()),
        TransactionValue(TOptional<FString>()),
        RandomStatusValue(nullptr),
        ExecuteTimeValue(TOptional<int32>()),
        ChargedValue(TOptional<int32>()),
        OutputValue(nullptr)
    {
    }

    FInvokeScriptResult::FInvokeScriptResult(
        const FInvokeScriptResult& From
    ):
        CodeValue(From.CodeValue),
        ResultValue(From.ResultValue),
        TransactionValue(From.TransactionValue),
        RandomStatusValue(From.RandomStatusValue),
        ExecuteTimeValue(From.ExecuteTimeValue),
        ChargedValue(From.ChargedValue),
        OutputValue(From.OutputValue)
    {
    }

    TSharedPtr<FInvokeScriptResult> FInvokeScriptResult::WithCode(
        const TOptional<int32> Code
    )
    {
        this->CodeValue = Code;
        return SharedThis(this);
    }

    TSharedPtr<FInvokeScriptResult> FInvokeScriptResult::WithResult(
        const TOptional<FString> Result
    )
    {
        this->ResultValue = Result;
        return SharedThis(this);
    }

    TSharedPtr<FInvokeScriptResult> FInvokeScriptResult::WithTransaction(
        const TOptional<FString> Transaction
    )
    {
        this->TransactionValue = Transaction;
        return SharedThis(this);
    }

    TSharedPtr<FInvokeScriptResult> FInvokeScriptResult::WithRandomStatus(
        const TSharedPtr<Model::FRandomStatus> RandomStatus
    )
    {
        this->RandomStatusValue = RandomStatus;
        return SharedThis(this);
    }

    TSharedPtr<FInvokeScriptResult> FInvokeScriptResult::WithExecuteTime(
        const TOptional<int32> ExecuteTime
    )
    {
        this->ExecuteTimeValue = ExecuteTime;
        return SharedThis(this);
    }

    TSharedPtr<FInvokeScriptResult> FInvokeScriptResult::WithCharged(
        const TOptional<int32> Charged
    )
    {
        this->ChargedValue = Charged;
        return SharedThis(this);
    }

    TSharedPtr<FInvokeScriptResult> FInvokeScriptResult::WithOutput(
        const TSharedPtr<TArray<FString>> Output
    )
    {
        this->OutputValue = Output;
        return SharedThis(this);
    }

    TOptional<int32> FInvokeScriptResult::GetCode() const
    {
        return CodeValue;
    }

    FString FInvokeScriptResult::GetCodeString() const
    {
        if (!CodeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CodeValue.GetValue());
    }

    TOptional<FString> FInvokeScriptResult::GetResult() const
    {
        return ResultValue;
    }

    TOptional<FString> FInvokeScriptResult::GetTransaction() const
    {
        return TransactionValue;
    }

    TSharedPtr<Model::FRandomStatus> FInvokeScriptResult::GetRandomStatus() const
    {
        if (!RandomStatusValue.IsValid())
        {
            return nullptr;
        }
        return RandomStatusValue;
    }

    TOptional<int32> FInvokeScriptResult::GetExecuteTime() const
    {
        return ExecuteTimeValue;
    }

    FString FInvokeScriptResult::GetExecuteTimeString() const
    {
        if (!ExecuteTimeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ExecuteTimeValue.GetValue());
    }

    TOptional<int32> FInvokeScriptResult::GetCharged() const
    {
        return ChargedValue;
    }

    FString FInvokeScriptResult::GetChargedString() const
    {
        if (!ChargedValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ChargedValue.GetValue());
    }

    TSharedPtr<TArray<FString>> FInvokeScriptResult::GetOutput() const
    {
        if (!OutputValue.IsValid())
        {
            return nullptr;
        }
        return OutputValue;
    }

    TSharedPtr<FInvokeScriptResult> FInvokeScriptResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FInvokeScriptResult>()
            ->WithCode(Data->HasField("code") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("code", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithResult(Data->HasField("result") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("result", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTransaction(Data->HasField("transaction") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("transaction", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRandomStatus(Data->HasField("randomStatus") ? [Data]() -> Model::FRandomStatusPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("randomStatus"))
                    {
                        return nullptr;
                    }
                    return Model::FRandomStatus::FromJson(Data->GetObjectField("randomStatus"));
                 }() : nullptr)
            ->WithExecuteTime(Data->HasField("executeTime") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("executeTime", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithCharged(Data->HasField("charged") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("charged", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithOutput(Data->HasField("output") ? [Data]() -> TSharedPtr<TArray<FString>>
                 {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>("output") && Data->HasTypedField<EJson::Array>("output"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("output"))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FInvokeScriptResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (CodeValue.IsSet())
        {
            JsonRootObject->SetNumberField("code", CodeValue.GetValue());
        }
        if (ResultValue.IsSet())
        {
            JsonRootObject->SetStringField("result", ResultValue.GetValue());
        }
        if (TransactionValue.IsSet())
        {
            JsonRootObject->SetStringField("transaction", TransactionValue.GetValue());
        }
        if (RandomStatusValue != nullptr && RandomStatusValue.IsValid())
        {
            JsonRootObject->SetObjectField("randomStatus", RandomStatusValue->ToJson());
        }
        if (ExecuteTimeValue.IsSet())
        {
            JsonRootObject->SetNumberField("executeTime", ExecuteTimeValue.GetValue());
        }
        if (ChargedValue.IsSet())
        {
            JsonRootObject->SetNumberField("charged", ChargedValue.GetValue());
        }
        if (OutputValue != nullptr && OutputValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *OutputValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("output", v);
        }
        return JsonRootObject;
    }
}