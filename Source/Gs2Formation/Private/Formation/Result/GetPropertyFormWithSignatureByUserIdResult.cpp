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

#include "Formation/Result/GetPropertyFormWithSignatureByUserIdResult.h"

namespace Gs2::Formation::Result
{
    FGetPropertyFormWithSignatureByUserIdResult::FGetPropertyFormWithSignatureByUserIdResult():
        ItemValue(nullptr),
        BodyValue(TOptional<FString>()),
        SignatureValue(TOptional<FString>()),
        PropertyFormModelValue(nullptr)
    {
    }

    FGetPropertyFormWithSignatureByUserIdResult::FGetPropertyFormWithSignatureByUserIdResult(
        const FGetPropertyFormWithSignatureByUserIdResult& From
    ):
        ItemValue(From.ItemValue),
        BodyValue(From.BodyValue),
        SignatureValue(From.SignatureValue),
        PropertyFormModelValue(From.PropertyFormModelValue)
    {
    }

    TSharedPtr<FGetPropertyFormWithSignatureByUserIdResult> FGetPropertyFormWithSignatureByUserIdResult::WithItem(
        const TSharedPtr<Model::FPropertyForm> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FGetPropertyFormWithSignatureByUserIdResult> FGetPropertyFormWithSignatureByUserIdResult::WithBody(
        const TOptional<FString> Body
    )
    {
        this->BodyValue = Body;
        return SharedThis(this);
    }

    TSharedPtr<FGetPropertyFormWithSignatureByUserIdResult> FGetPropertyFormWithSignatureByUserIdResult::WithSignature(
        const TOptional<FString> Signature
    )
    {
        this->SignatureValue = Signature;
        return SharedThis(this);
    }

    TSharedPtr<FGetPropertyFormWithSignatureByUserIdResult> FGetPropertyFormWithSignatureByUserIdResult::WithPropertyFormModel(
        const TSharedPtr<Model::FPropertyFormModel> PropertyFormModel
    )
    {
        this->PropertyFormModelValue = PropertyFormModel;
        return SharedThis(this);
    }

    TSharedPtr<Model::FPropertyForm> FGetPropertyFormWithSignatureByUserIdResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TOptional<FString> FGetPropertyFormWithSignatureByUserIdResult::GetBody() const
    {
        return BodyValue;
    }

    TOptional<FString> FGetPropertyFormWithSignatureByUserIdResult::GetSignature() const
    {
        return SignatureValue;
    }

    TSharedPtr<Model::FPropertyFormModel> FGetPropertyFormWithSignatureByUserIdResult::GetPropertyFormModel() const
    {
        if (!PropertyFormModelValue.IsValid())
        {
            return nullptr;
        }
        return PropertyFormModelValue;
    }

    TSharedPtr<FGetPropertyFormWithSignatureByUserIdResult> FGetPropertyFormWithSignatureByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetPropertyFormWithSignatureByUserIdResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FPropertyFormPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FPropertyForm::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr)
            ->WithBody(Data->HasField(ANSI_TO_TCHAR("body")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("body"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithSignature(Data->HasField(ANSI_TO_TCHAR("signature")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("signature"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithPropertyFormModel(Data->HasField(ANSI_TO_TCHAR("propertyFormModel")) ? [Data]() -> Model::FPropertyFormModelPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("propertyFormModel")))
                    {
                        return nullptr;
                    }
                    return Model::FPropertyFormModel::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("propertyFormModel")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FGetPropertyFormWithSignatureByUserIdResult::ToJson() const
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
        if (PropertyFormModelValue != nullptr && PropertyFormModelValue.IsValid())
        {
            JsonRootObject->SetObjectField("propertyFormModel", PropertyFormModelValue->ToJson());
        }
        return JsonRootObject;
    }
}