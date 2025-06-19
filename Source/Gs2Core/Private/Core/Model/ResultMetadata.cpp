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
        UncommittedValue(FString())
    {
    }

    FResultMetadata::FResultMetadata(
        const FResultMetadata& From
    ):
        UncommittedValue(From.UncommittedValue)
    {
    }

    TSharedPtr<FResultMetadata> FResultMetadata::WithUncommitted(
        const FString Uncommitted
    )
    {
        this->UncommittedValue = Uncommitted;
        return SharedThis(this);
    }
    FString FResultMetadata::GetUncommitted() const
    {
        return UncommittedValue;
    }

    TSharedPtr<FResultMetadata> FResultMetadata::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FResultMetadata>()
            ->WithUncommitted(Data->HasField(ANSI_TO_TCHAR("uncommitted")) ? [Data]() -> FString
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("uncommitted")))
                    {
                        return FString();
                    }
                    return FString(ANSI_TO_TCHAR("uncommitted"));
                 }() : FString());
    }

    TSharedPtr<FJsonObject> FResultMetadata::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (UncommittedValue.IsEmpty())
        {
            JsonRootObject->SetStringField("uncommitted", UncommittedValue);
        }
        return JsonRootObject;
    }

    FString FResultMetadata::TypeName = "ResultMetadata";
}