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

#include "Formation/Result/GetPropertyFormWithSignatureResult.h"

namespace Gs2::Formation::Result
{
    FGetPropertyFormWithSignatureResult::FGetPropertyFormWithSignatureResult():
        ItemValue(nullptr),
        BodyValue(TOptional<FString>()),
        SignatureValue(TOptional<FString>()),
        FormModelValue(nullptr)
    {
    }

    FGetPropertyFormWithSignatureResult::FGetPropertyFormWithSignatureResult(
        const FGetPropertyFormWithSignatureResult& From
    ):
        ItemValue(From.ItemValue),
        BodyValue(From.BodyValue),
        SignatureValue(From.SignatureValue),
        FormModelValue(From.FormModelValue)
    {
    }

    TSharedPtr<FGetPropertyFormWithSignatureResult> FGetPropertyFormWithSignatureResult::WithItem(
        const TSharedPtr<Model::FPropertyForm> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FGetPropertyFormWithSignatureResult> FGetPropertyFormWithSignatureResult::WithBody(
        const TOptional<FString> Body
    )
    {
        this->BodyValue = Body;
        return SharedThis(this);
    }

    TSharedPtr<FGetPropertyFormWithSignatureResult> FGetPropertyFormWithSignatureResult::WithSignature(
        const TOptional<FString> Signature
    )
    {
        this->SignatureValue = Signature;
        return SharedThis(this);
    }

    TSharedPtr<FGetPropertyFormWithSignatureResult> FGetPropertyFormWithSignatureResult::WithFormModel(
        const TSharedPtr<Model::FFormModel> FormModel
    )
    {
        this->FormModelValue = FormModel;
        return SharedThis(this);
    }

    TSharedPtr<Model::FPropertyForm> FGetPropertyFormWithSignatureResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TOptional<FString> FGetPropertyFormWithSignatureResult::GetBody() const
    {
        return BodyValue;
    }

    TOptional<FString> FGetPropertyFormWithSignatureResult::GetSignature() const
    {
        return SignatureValue;
    }

    TSharedPtr<Model::FFormModel> FGetPropertyFormWithSignatureResult::GetFormModel() const
    {
        if (!FormModelValue.IsValid())
        {
            return nullptr;
        }
        return FormModelValue;
    }

    TSharedPtr<FGetPropertyFormWithSignatureResult> FGetPropertyFormWithSignatureResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetPropertyFormWithSignatureResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FPropertyFormPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FPropertyForm::FromJson(Data->GetObjectField("item"));
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
                }() : TOptional<FString>())
            ->WithFormModel(Data->HasField("formModel") ? [Data]() -> Model::FFormModelPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("formModel"))
                    {
                        return nullptr;
                    }
                    return Model::FFormModel::FromJson(Data->GetObjectField("formModel"));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FGetPropertyFormWithSignatureResult::ToJson() const
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
        if (FormModelValue != nullptr && FormModelValue.IsValid())
        {
            JsonRootObject->SetObjectField("formModel", FormModelValue->ToJson());
        }
        return JsonRootObject;
    }
}