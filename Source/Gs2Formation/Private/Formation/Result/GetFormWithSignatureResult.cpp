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

#include "Formation/Result/GetFormWithSignatureResult.h"

namespace Gs2::Formation::Result
{
    FGetFormWithSignatureResult::FGetFormWithSignatureResult():
        ItemValue(nullptr),
        BodyValue(TOptional<FString>()),
        SignatureValue(TOptional<FString>()),
        MoldValue(nullptr),
        MoldModelValue(nullptr),
        FormModelValue(nullptr)
    {
    }

    FGetFormWithSignatureResult::FGetFormWithSignatureResult(
        const FGetFormWithSignatureResult& From
    ):
        ItemValue(From.ItemValue),
        BodyValue(From.BodyValue),
        SignatureValue(From.SignatureValue),
        MoldValue(From.MoldValue),
        MoldModelValue(From.MoldModelValue),
        FormModelValue(From.FormModelValue)
    {
    }

    TSharedPtr<FGetFormWithSignatureResult> FGetFormWithSignatureResult::WithItem(
        const TSharedPtr<Model::FForm> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FGetFormWithSignatureResult> FGetFormWithSignatureResult::WithBody(
        const TOptional<FString> Body
    )
    {
        this->BodyValue = Body;
        return SharedThis(this);
    }

    TSharedPtr<FGetFormWithSignatureResult> FGetFormWithSignatureResult::WithSignature(
        const TOptional<FString> Signature
    )
    {
        this->SignatureValue = Signature;
        return SharedThis(this);
    }

    TSharedPtr<FGetFormWithSignatureResult> FGetFormWithSignatureResult::WithMold(
        const TSharedPtr<Model::FMold> Mold
    )
    {
        this->MoldValue = Mold;
        return SharedThis(this);
    }

    TSharedPtr<FGetFormWithSignatureResult> FGetFormWithSignatureResult::WithMoldModel(
        const TSharedPtr<Model::FMoldModel> MoldModel
    )
    {
        this->MoldModelValue = MoldModel;
        return SharedThis(this);
    }

    TSharedPtr<FGetFormWithSignatureResult> FGetFormWithSignatureResult::WithFormModel(
        const TSharedPtr<Model::FFormModel> FormModel
    )
    {
        this->FormModelValue = FormModel;
        return SharedThis(this);
    }

    TSharedPtr<Model::FForm> FGetFormWithSignatureResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TOptional<FString> FGetFormWithSignatureResult::GetBody() const
    {
        return BodyValue;
    }

    TOptional<FString> FGetFormWithSignatureResult::GetSignature() const
    {
        return SignatureValue;
    }

    TSharedPtr<Model::FMold> FGetFormWithSignatureResult::GetMold() const
    {
        if (!MoldValue.IsValid())
        {
            return nullptr;
        }
        return MoldValue;
    }

    TSharedPtr<Model::FMoldModel> FGetFormWithSignatureResult::GetMoldModel() const
    {
        if (!MoldModelValue.IsValid())
        {
            return nullptr;
        }
        return MoldModelValue;
    }

    TSharedPtr<Model::FFormModel> FGetFormWithSignatureResult::GetFormModel() const
    {
        if (!FormModelValue.IsValid())
        {
            return nullptr;
        }
        return FormModelValue;
    }

    TSharedPtr<FGetFormWithSignatureResult> FGetFormWithSignatureResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetFormWithSignatureResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FFormPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FForm::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
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
            ->WithMold(Data->HasField(ANSI_TO_TCHAR("mold")) ? [Data]() -> Model::FMoldPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("mold")))
                    {
                        return nullptr;
                    }
                    return Model::FMold::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("mold")));
                 }() : nullptr)
            ->WithMoldModel(Data->HasField(ANSI_TO_TCHAR("moldModel")) ? [Data]() -> Model::FMoldModelPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("moldModel")))
                    {
                        return nullptr;
                    }
                    return Model::FMoldModel::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("moldModel")));
                 }() : nullptr)
            ->WithFormModel(Data->HasField(ANSI_TO_TCHAR("formModel")) ? [Data]() -> Model::FFormModelPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("formModel")))
                    {
                        return nullptr;
                    }
                    return Model::FFormModel::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("formModel")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FGetFormWithSignatureResult::ToJson() const
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