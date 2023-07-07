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

#include "Inventory/Result/GetSimpleItemWithSignatureResult.h"

namespace Gs2::Inventory::Result
{
    FGetSimpleItemWithSignatureResult::FGetSimpleItemWithSignatureResult():
        ItemValue(nullptr),
        SimpleItemModelValue(nullptr),
        BodyValue(TOptional<FString>()),
        SignatureValue(TOptional<FString>())
    {
    }

    FGetSimpleItemWithSignatureResult::FGetSimpleItemWithSignatureResult(
        const FGetSimpleItemWithSignatureResult& From
    ):
        ItemValue(From.ItemValue),
        SimpleItemModelValue(From.SimpleItemModelValue),
        BodyValue(From.BodyValue),
        SignatureValue(From.SignatureValue)
    {
    }

    TSharedPtr<FGetSimpleItemWithSignatureResult> FGetSimpleItemWithSignatureResult::WithItem(
        const TSharedPtr<Model::FSimpleItem> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FGetSimpleItemWithSignatureResult> FGetSimpleItemWithSignatureResult::WithSimpleItemModel(
        const TSharedPtr<Model::FSimpleItemModel> SimpleItemModel
    )
    {
        this->SimpleItemModelValue = SimpleItemModel;
        return SharedThis(this);
    }

    TSharedPtr<FGetSimpleItemWithSignatureResult> FGetSimpleItemWithSignatureResult::WithBody(
        const TOptional<FString> Body
    )
    {
        this->BodyValue = Body;
        return SharedThis(this);
    }

    TSharedPtr<FGetSimpleItemWithSignatureResult> FGetSimpleItemWithSignatureResult::WithSignature(
        const TOptional<FString> Signature
    )
    {
        this->SignatureValue = Signature;
        return SharedThis(this);
    }

    TSharedPtr<Model::FSimpleItem> FGetSimpleItemWithSignatureResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FSimpleItemModel> FGetSimpleItemWithSignatureResult::GetSimpleItemModel() const
    {
        if (!SimpleItemModelValue.IsValid())
        {
            return nullptr;
        }
        return SimpleItemModelValue;
    }

    TOptional<FString> FGetSimpleItemWithSignatureResult::GetBody() const
    {
        return BodyValue;
    }

    TOptional<FString> FGetSimpleItemWithSignatureResult::GetSignature() const
    {
        return SignatureValue;
    }

    TSharedPtr<FGetSimpleItemWithSignatureResult> FGetSimpleItemWithSignatureResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetSimpleItemWithSignatureResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FSimpleItemPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FSimpleItem::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithSimpleItemModel(Data->HasField("simpleItemModel") ? [Data]() -> Model::FSimpleItemModelPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("simpleItemModel"))
                    {
                        return nullptr;
                    }
                    return Model::FSimpleItemModel::FromJson(Data->GetObjectField("simpleItemModel"));
                 }() : nullptr)
            ->WithBody(Data->HasField("body") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("body", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithSignature(Data->HasField("signature") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("signature", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetSimpleItemWithSignatureResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (SimpleItemModelValue != nullptr && SimpleItemModelValue.IsValid())
        {
            JsonRootObject->SetObjectField("simpleItemModel", SimpleItemModelValue->ToJson());
        }
        if (BodyValue.IsSet())
        {
            JsonRootObject->SetStringField("body", BodyValue.GetValue());
        }
        if (SignatureValue.IsSet())
        {
            JsonRootObject->SetStringField("signature", SignatureValue.GetValue());
        }
        return JsonRootObject;
    }
}