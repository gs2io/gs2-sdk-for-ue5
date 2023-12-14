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

#include "Script/Result/DebugInvokeResult.h"

namespace Gs2::Script::Result
{
    FDebugInvokeResult::FDebugInvokeResult():
        CodeValue(TOptional<int32>()),
        ResultValue(TOptional<FString>()),
        TransactionValue(nullptr),
        RandomStatusValue(nullptr),
        ExecuteTimeValue(TOptional<int32>()),
        ChargedValue(TOptional<int32>()),
        OutputValue(nullptr)
    {
    }

    FDebugInvokeResult::FDebugInvokeResult(
        const FDebugInvokeResult& From
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

    TSharedPtr<FDebugInvokeResult> FDebugInvokeResult::WithCode(
        const TOptional<int32> Code
    )
    {
        this->CodeValue = Code;
        return SharedThis(this);
    }

    TSharedPtr<FDebugInvokeResult> FDebugInvokeResult::WithResult(
        const TOptional<FString> Result
    )
    {
        this->ResultValue = Result;
        return SharedThis(this);
    }

    TSharedPtr<FDebugInvokeResult> FDebugInvokeResult::WithTransaction(
        const TSharedPtr<Model::FTransaction> Transaction
    )
    {
        this->TransactionValue = Transaction;
        return SharedThis(this);
    }

    TSharedPtr<FDebugInvokeResult> FDebugInvokeResult::WithRandomStatus(
        const TSharedPtr<Model::FRandomStatus> RandomStatus
    )
    {
        this->RandomStatusValue = RandomStatus;
        return SharedThis(this);
    }

    TSharedPtr<FDebugInvokeResult> FDebugInvokeResult::WithExecuteTime(
        const TOptional<int32> ExecuteTime
    )
    {
        this->ExecuteTimeValue = ExecuteTime;
        return SharedThis(this);
    }

    TSharedPtr<FDebugInvokeResult> FDebugInvokeResult::WithCharged(
        const TOptional<int32> Charged
    )
    {
        this->ChargedValue = Charged;
        return SharedThis(this);
    }

    TSharedPtr<FDebugInvokeResult> FDebugInvokeResult::WithOutput(
        const TSharedPtr<TArray<FString>> Output
    )
    {
        this->OutputValue = Output;
        return SharedThis(this);
    }

    TOptional<int32> FDebugInvokeResult::GetCode() const
    {
        return CodeValue;
    }

    FString FDebugInvokeResult::GetCodeString() const
    {
        if (!CodeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CodeValue.GetValue());
    }

    TOptional<FString> FDebugInvokeResult::GetResult() const
    {
        return ResultValue;
    }

    TSharedPtr<Model::FTransaction> FDebugInvokeResult::GetTransaction() const
    {
        if (!TransactionValue.IsValid())
        {
            return nullptr;
        }
        return TransactionValue;
    }

    TSharedPtr<Model::FRandomStatus> FDebugInvokeResult::GetRandomStatus() const
    {
        if (!RandomStatusValue.IsValid())
        {
            return nullptr;
        }
        return RandomStatusValue;
    }

    TOptional<int32> FDebugInvokeResult::GetExecuteTime() const
    {
        return ExecuteTimeValue;
    }

    FString FDebugInvokeResult::GetExecuteTimeString() const
    {
        if (!ExecuteTimeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ExecuteTimeValue.GetValue());
    }

    TOptional<int32> FDebugInvokeResult::GetCharged() const
    {
        return ChargedValue;
    }

    FString FDebugInvokeResult::GetChargedString() const
    {
        if (!ChargedValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ChargedValue.GetValue());
    }

    TSharedPtr<TArray<FString>> FDebugInvokeResult::GetOutput() const
    {
        if (!OutputValue.IsValid())
        {
            return nullptr;
        }
        return OutputValue;
    }

    TSharedPtr<FDebugInvokeResult> FDebugInvokeResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDebugInvokeResult>()
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
            ->WithTransaction(Data->HasField("transaction") ? [Data]() -> Model::FTransactionPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("transaction"))
                    {
                        return nullptr;
                    }
                    return Model::FTransaction::FromJson(Data->GetObjectField("transaction"));
                 }() : nullptr)
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

    TSharedPtr<FJsonObject> FDebugInvokeResult::ToJson() const
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
        if (TransactionValue != nullptr && TransactionValue.IsValid())
        {
            JsonRootObject->SetObjectField("transaction", TransactionValue->ToJson());
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