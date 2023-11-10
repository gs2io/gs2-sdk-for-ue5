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

#include "Datastore/Result/PrepareReUploadResult.h"

namespace Gs2::Datastore::Result
{
    FPrepareReUploadResult::FPrepareReUploadResult():
        ItemValue(nullptr),
        UploadUrlValue(TOptional<FString>())
    {
    }

    FPrepareReUploadResult::FPrepareReUploadResult(
        const FPrepareReUploadResult& From
    ):
        ItemValue(From.ItemValue),
        UploadUrlValue(From.UploadUrlValue)
    {
    }

    TSharedPtr<FPrepareReUploadResult> FPrepareReUploadResult::WithItem(
        const TSharedPtr<Model::FDataObject> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareReUploadResult> FPrepareReUploadResult::WithUploadUrl(
        const TOptional<FString> UploadUrl
    )
    {
        this->UploadUrlValue = UploadUrl;
        return SharedThis(this);
    }

    TSharedPtr<Model::FDataObject> FPrepareReUploadResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TOptional<FString> FPrepareReUploadResult::GetUploadUrl() const
    {
        return UploadUrlValue;
    }

    TSharedPtr<FPrepareReUploadResult> FPrepareReUploadResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPrepareReUploadResult>()
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

    TSharedPtr<FJsonObject> FPrepareReUploadResult::ToJson() const
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