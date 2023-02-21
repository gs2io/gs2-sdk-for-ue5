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

#include "Dictionary/Result/GetEntryWithSignatureByUserIdResult.h"

namespace Gs2::Dictionary::Result
{
    FGetEntryWithSignatureByUserIdResult::FGetEntryWithSignatureByUserIdResult():
        ItemValue(nullptr),
        BodyValue(TOptional<FString>()),
        SignatureValue(TOptional<FString>())
    {
    }

    FGetEntryWithSignatureByUserIdResult::FGetEntryWithSignatureByUserIdResult(
        const FGetEntryWithSignatureByUserIdResult& From
    ):
        ItemValue(From.ItemValue),
        BodyValue(From.BodyValue),
        SignatureValue(From.SignatureValue)
    {
    }

    TSharedPtr<FGetEntryWithSignatureByUserIdResult> FGetEntryWithSignatureByUserIdResult::WithItem(
        const TSharedPtr<Model::FEntry> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FGetEntryWithSignatureByUserIdResult> FGetEntryWithSignatureByUserIdResult::WithBody(
        const TOptional<FString> Body
    )
    {
        this->BodyValue = Body;
        return SharedThis(this);
    }

    TSharedPtr<FGetEntryWithSignatureByUserIdResult> FGetEntryWithSignatureByUserIdResult::WithSignature(
        const TOptional<FString> Signature
    )
    {
        this->SignatureValue = Signature;
        return SharedThis(this);
    }

    TSharedPtr<Model::FEntry> FGetEntryWithSignatureByUserIdResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TOptional<FString> FGetEntryWithSignatureByUserIdResult::GetBody() const
    {
        return BodyValue;
    }

    TOptional<FString> FGetEntryWithSignatureByUserIdResult::GetSignature() const
    {
        return SignatureValue;
    }

    TSharedPtr<FGetEntryWithSignatureByUserIdResult> FGetEntryWithSignatureByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetEntryWithSignatureByUserIdResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FEntryPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FEntry::FromJson(Data->GetObjectField("item"));
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

    TSharedPtr<FJsonObject> FGetEntryWithSignatureByUserIdResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
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