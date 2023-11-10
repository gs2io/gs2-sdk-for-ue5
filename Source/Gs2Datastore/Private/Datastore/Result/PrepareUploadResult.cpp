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

#include "Datastore/Result/PrepareUploadResult.h"

namespace Gs2::Datastore::Result
{
    FPrepareUploadResult::FPrepareUploadResult():
        ItemValue(nullptr),
        UploadUrlValue(TOptional<FString>())
    {
    }

    FPrepareUploadResult::FPrepareUploadResult(
        const FPrepareUploadResult& From
    ):
        ItemValue(From.ItemValue),
        UploadUrlValue(From.UploadUrlValue)
    {
    }

    TSharedPtr<FPrepareUploadResult> FPrepareUploadResult::WithItem(
        const TSharedPtr<Model::FDataObject> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareUploadResult> FPrepareUploadResult::WithUploadUrl(
        const TOptional<FString> UploadUrl
    )
    {
        this->UploadUrlValue = UploadUrl;
        return SharedThis(this);
    }

    TSharedPtr<Model::FDataObject> FPrepareUploadResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TOptional<FString> FPrepareUploadResult::GetUploadUrl() const
    {
        return UploadUrlValue;
    }

    TSharedPtr<FPrepareUploadResult> FPrepareUploadResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPrepareUploadResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FDataObjectPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FDataObject::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithUploadUrl(Data->HasField("uploadUrl") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("uploadUrl", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FPrepareUploadResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (UploadUrlValue.IsSet())
        {
            JsonRootObject->SetStringField("uploadUrl", UploadUrlValue.GetValue());
        }
        return JsonRootObject;
    }
}