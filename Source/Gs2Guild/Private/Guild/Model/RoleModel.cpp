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

#include "Guild/Model/RoleModel.h"

namespace Gs2::Guild::Model
{
    FRoleModel::FRoleModel():
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        PolicyDocumentValue(TOptional<FString>())
    {
    }

    FRoleModel::FRoleModel(
        const FRoleModel& From
    ):
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        PolicyDocumentValue(From.PolicyDocumentValue)
    {
    }

    TSharedPtr<FRoleModel> FRoleModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FRoleModel> FRoleModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FRoleModel> FRoleModel::WithPolicyDocument(
        const TOptional<FString> PolicyDocument
    )
    {
        this->PolicyDocumentValue = PolicyDocument;
        return SharedThis(this);
    }
    TOptional<FString> FRoleModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FRoleModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FRoleModel::GetPolicyDocument() const
    {
        return PolicyDocumentValue;
    }

    TSharedPtr<FRoleModel> FRoleModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRoleModel>()
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField(ANSI_TO_TCHAR("metadata")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("metadata"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithPolicyDocument(Data->HasField(ANSI_TO_TCHAR("policyDocument")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("policyDocument"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FRoleModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (PolicyDocumentValue.IsSet())
        {
            JsonRootObject->SetStringField("policyDocument", PolicyDocumentValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FRoleModel::TypeName = "RoleModel";
}