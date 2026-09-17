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
 *
 * deny overwrite
 */

#include "Core/Model/ResultMetadata.h"

namespace Gs2::Core::Model
{
    FResultMetadata::FResultMetadata():
        RequestIdValue(TOptional<FString>()),
        UncommittedValue(TOptional<FString>()),
        ScriptTransactionResultsValue(nullptr)
    {
    }

    FResultMetadata::FResultMetadata(
        const FResultMetadata& From
    ):
        RequestIdValue(From.RequestIdValue),
        UncommittedValue(From.UncommittedValue),
        ScriptTransactionResultsValue(From.ScriptTransactionResultsValue)
    {
    }

    TSharedPtr<FResultMetadata> FResultMetadata::WithRequestId(
        const TOptional<FString> RequestId
    )
    {
        this->RequestIdValue = RequestId;
        return SharedThis(this);
    }

    TSharedPtr<FResultMetadata> FResultMetadata::WithUncommitted(
        const FString Uncommitted
    )
    {
        this->UncommittedValue = TOptional<FString>(Uncommitted);
        return SharedThis(this);
    }

    TSharedPtr<FResultMetadata> FResultMetadata::WithUncommitted(
        const TOptional<FString> Uncommitted
    )
    {
        this->UncommittedValue = Uncommitted;
        return SharedThis(this);
    }

    TSharedPtr<FResultMetadata> FResultMetadata::WithScriptTransactionResults(
        const TSharedPtr<TArray<TSharedPtr<FScriptTransactionResult>>> ScriptTransactionResults
    )
    {
        this->ScriptTransactionResultsValue = ScriptTransactionResults;
        return SharedThis(this);
    }

    TOptional<FString> FResultMetadata::GetRequestId() const
    {
        return RequestIdValue;
    }

    FString FResultMetadata::GetUncommitted() const
    {
        return UncommittedValue.IsSet() ? UncommittedValue.GetValue() : FString();
    }

    TSharedPtr<TArray<TSharedPtr<FScriptTransactionResult>>> FResultMetadata::GetScriptTransactionResults() const
    {
        return ScriptTransactionResultsValue;
    }

    TSharedPtr<FResultMetadata> FResultMetadata::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FResultMetadata>()
            ->WithRequestId(Data->HasField(ANSI_TO_TCHAR("requestId")) ? [Data]() -> TOptional<FString>
                {
                    FString Value;
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("requestId"), Value))
                    {
                        return TOptional<FString>(Value);
                    }
                    return TOptional<FString>();
                 }() : TOptional<FString>())
            ->WithUncommitted(Data->HasField(ANSI_TO_TCHAR("uncommitted")) ? [Data]() -> TOptional<FString>
                {
                    FString Value;
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("uncommitted"), Value))
                    {
                        return TOptional<FString>(Value);
                    }
                    return TOptional<FString>();
                 }() : TOptional<FString>())
            ->WithScriptTransactionResults(Data->HasField(ANSI_TO_TCHAR("scriptTransactionResults")) ? [Data]() -> TSharedPtr<TArray<TSharedPtr<FScriptTransactionResult>>>
                {
                    auto Value = MakeShared<TArray<TSharedPtr<FScriptTransactionResult>>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("scriptTransactionResults")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("scriptTransactionResults")))
                    {
                        for (const auto& JsonValue : Data->GetArrayField(ANSI_TO_TCHAR("scriptTransactionResults")))
                        {
                            if (JsonValue.IsValid() && JsonValue->Type == EJson::Object)
                            {
                                const auto Item = FScriptTransactionResult::FromJson(JsonValue->AsObject());
                                if (Item.IsValid())
                                {
                                    Value->Add(Item);
                                }
                            }
                        }
                    }
                    return Value;
                }() : MakeShared<TArray<TSharedPtr<FScriptTransactionResult>>>());
    }

    TSharedPtr<FJsonObject> FResultMetadata::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (RequestIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("requestId"), RequestIdValue.GetValue());
        }
        if (UncommittedValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("uncommitted"), UncommittedValue.GetValue());
        }
        if (ScriptTransactionResultsValue.IsValid() && ScriptTransactionResultsValue->Num() > 0)
        {
            TArray<TSharedPtr<FJsonValue>> Values;
            for (const auto& Item : *ScriptTransactionResultsValue)
            {
                if (Item.IsValid())
                {
                    Values.Add(MakeShared<FJsonValueObject>(Item->ToJson()));
                }
            }
            JsonRootObject->SetArrayField(TEXT("scriptTransactionResults"), Values);
        }
        return JsonRootObject;
    }

    FString FResultMetadata::TypeName = "ResultMetadata";
}