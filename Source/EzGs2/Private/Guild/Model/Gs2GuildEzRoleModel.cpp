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

#include "Guild/Model/Gs2GuildEzRoleModel.h"

namespace Gs2::UE5::Guild::Model
{

    TSharedPtr<FEzRoleModel> FEzRoleModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzRoleModel> FEzRoleModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzRoleModel> FEzRoleModel::WithPolicyDocument(
        const TOptional<FString> PolicyDocument
    )
    {
        this->PolicyDocumentValue = PolicyDocument;
        return SharedThis(this);
    }
    TOptional<FString> FEzRoleModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzRoleModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FEzRoleModel::GetPolicyDocument() const
    {
        return PolicyDocumentValue;
    }

    Gs2::Guild::Model::FRoleModelPtr FEzRoleModel::ToModel() const
    {
        return MakeShared<Gs2::Guild::Model::FRoleModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithPolicyDocument(PolicyDocumentValue);
    }

    TSharedPtr<FEzRoleModel> FEzRoleModel::FromModel(const Gs2::Guild::Model::FRoleModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzRoleModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithPolicyDocument(Model->GetPolicyDocument());
    }
}