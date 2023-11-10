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

#include "Formation/Result/GetFormWithSignatureByUserIdResult.h"

namespace Gs2::Formation::Result
{
    FGetFormWithSignatureByUserIdResult::FGetFormWithSignatureByUserIdResult():
        ItemValue(nullptr),
        BodyValue(TOptional<FString>()),
        SignatureValue(TOptional<FString>()),
        MoldValue(nullptr),
        MoldModelValue(nullptr),
        FormModelValue(nullptr)
    {
    }

    FGetFormWithSignatureByUserIdResult::FGetFormWithSignatureByUserIdResult(
        const FGetFormWithSignatureByUserIdResult& From
    ):
        ItemValue(From.ItemValue),
        BodyValue(From.BodyValue),
        SignatureValue(From.SignatureValue),
        MoldValue(From.MoldValue),
        MoldModelValue(From.MoldModelValue),
        FormModelValue(From.FormModelValue)
    {
    }

    TSharedPtr<FGetFormWithSignatureByUserIdResult> FGetFormWithSignatureByUserIdResult::WithItem(
        const TSharedPtr<Model::FForm> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FGetFormWithSignatureByUserIdResult> FGetFormWithSignatureByUserIdResult::WithBody(
        const TOptional<FString> Body
    )
    {
        this->BodyValue = Body;
        return SharedThis(this);
    }

    TSharedPtr<FGetFormWithSignatureByUserIdResult> FGetFormWithSignatureByUserIdResult::WithSignature(
        const TOptional<FString> Signature
    )
    {
        this->SignatureValue = Signature;
        return SharedThis(this);
    }

    TSharedPtr<FGetFormWithSignatureByUserIdResult> FGetFormWithSignatureByUserIdResult::WithMold(
        const TSharedPtr<Model::FMold> Mold
    )
    {
        this->MoldValue = Mold;
        return SharedThis(this);
    }

    TSharedPtr<FGetFormWithSignatureByUserIdResult> FGetFormWithSignatureByUserIdResult::WithMoldModel(
        const TSharedPtr<Model::FMoldModel> MoldModel
    )
    {
        this->MoldModelValue = MoldModel;
        return SharedThis(this);
    }

    TSharedPtr<FGetFormWithSignatureByUserIdResult> FGetFormWithSignatureByUserIdResult::WithFormModel(
        const TSharedPtr<Model::FFormModel> FormModel
    )
    {
        this->FormModelValue = FormModel;
        return SharedThis(this);
    }

    TSharedPtr<Model::FForm> FGetFormWithSignatureByUserIdResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TOptional<FString> FGetFormWithSignatureByUserIdResult::GetBody() const
    {
        return BodyValue;
    }

    TOptional<FString> FGetFormWithSignatureByUserIdResult::GetSignature() const
    {
        return SignatureValue;
    }

    TSharedPtr<Model::FMold> FGetFormWithSignatureByUserIdResult::GetMold() const
    {
        if (!MoldValue.IsValid())
        {
            return nullptr;
        }
        return MoldValue;
    }

    TSharedPtr<Model::FMoldModel> FGetFormWithSignatureByUserIdResult::GetMoldModel() const
    {
        if (!MoldModelValue.IsValid())
        {
            return nullptr;
        }
        return MoldModelValue;
    }

    TSharedPtr<Model::FFormModel> FGetFormWithSignatureByUserIdResult::GetFormModel() const
    {
        if (!FormModelValue.IsValid())
        {
            return nullptr;
        }
        return FormModelValue;
    }

    TSharedPtr<FGetFormWithSignatureByUserIdResult> FGetFormWithSignatureByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetFormWithSignatureByUserIdResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FFormPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FForm::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithBody(Data->HasField("body") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("body", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithSignature(Data->HasField("signature") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("signature", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMold(Data->HasField("mold") ? [Data]() -> Model::FMoldPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("mold"))
                    {
                        return nullptr;
                    }
                    return Model::FMold::FromJson(Data->GetObjectField("mold"));
                 }() : nullptr)
            ->WithMoldModel(Data->HasField("moldModel") ? [Data]() -> Model::FMoldModelPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("moldModel"))
                    {
                        return nullptr;
                    }
                    return Model::FMoldModel::FromJson(Data->GetObjectField("moldModel"));
                 }() : nullptr)
            ->WithFormModel(Data->HasField("formModel") ? [Data]() -> Model::FFormModelPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("formModel"))
                    {
                        return nullptr;
                    }
                    return Model::FFormModel::FromJson(Data->GetObjectField("formModel"));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FGetFormWithSignatureByUserIdResult::ToJson() const
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
        if (MoldValue != nullptr && MoldValue.IsValid())
        {
            JsonRootObject->SetObjectField("mold", MoldValue->ToJson());
        }
        if (MoldModelValue != nullptr && MoldModelValue.IsValid())
        {
            JsonRootObject->SetObjectField("moldModel", MoldModelValue->ToJson());
        }
        if (FormModelValue != nullptr && FormModelValue.IsValid())
        {
            JsonRootObject->SetObjectField("formModel", FormModelValue->ToJson());
        }
        return JsonRootObject;
    }
}