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

#include "Identifier/Result/CreateIdentifierResult.h"

namespace Gs2::Identifier::Result
{
    FCreateIdentifierResult::FCreateIdentifierResult():
        ItemValue(nullptr),
        ClientSecretValue(TOptional<FString>())
    {
    }

    FCreateIdentifierResult::FCreateIdentifierResult(
        const FCreateIdentifierResult& From
    ):
        ItemValue(From.ItemValue),
        ClientSecretValue(From.ClientSecretValue)
    {
    }

    TSharedPtr<FCreateIdentifierResult> FCreateIdentifierResult::WithItem(
        const TSharedPtr<Model::FIdentifier> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FCreateIdentifierResult> FCreateIdentifierResult::WithClientSecret(
        const TOptional<FString> ClientSecret
    )
    {
        this->ClientSecretValue = ClientSecret;
        return SharedThis(this);
    }

    TSharedPtr<Model::FIdentifier> FCreateIdentifierResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TOptional<FString> FCreateIdentifierResult::GetClientSecret() const
    {
        return ClientSecretValue;
    }

    TSharedPtr<FCreateIdentifierResult> FCreateIdentifierResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateIdentifierResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FIdentifierPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FIdentifier::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithClientSecret(Data->HasField("clientSecret") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("clientSecret", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FCreateIdentifierResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (ClientSecretValue.IsSet())
        {
            JsonRootObject->SetStringField("clientSecret", ClientSecretValue.GetValue());
        }
        return JsonRootObject;
    }
}