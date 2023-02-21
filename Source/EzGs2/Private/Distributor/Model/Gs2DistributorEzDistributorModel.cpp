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

#include "EzGs2/Public/Distributor/Model/Gs2DistributorEzDistributorModel.h"

namespace Gs2::UE5::Distributor::Model
{

    TSharedPtr<FEzDistributorModel> FEzDistributorModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzDistributorModel> FEzDistributorModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzDistributorModel> FEzDistributorModel::WithInboxNamespaceId(
        const TOptional<FString> InboxNamespaceId
    )
    {
        this->InboxNamespaceIdValue = InboxNamespaceId;
        return SharedThis(this);
    }

    TSharedPtr<FEzDistributorModel> FEzDistributorModel::WithWhiteListTargetIds(
        const TSharedPtr<TArray<FString>> WhiteListTargetIds
    )
    {
        this->WhiteListTargetIdsValue = WhiteListTargetIds;
        return SharedThis(this);
    }
    TOptional<FString> FEzDistributorModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzDistributorModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FEzDistributorModel::GetInboxNamespaceId() const
    {
        return InboxNamespaceIdValue;
    }
    TSharedPtr<TArray<FString>> FEzDistributorModel::GetWhiteListTargetIds() const
    {
        return WhiteListTargetIdsValue;
    }

    Gs2::Distributor::Model::FDistributorModelPtr FEzDistributorModel::ToModel() const
    {
        return MakeShared<Gs2::Distributor::Model::FDistributorModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithInboxNamespaceId(InboxNamespaceIdValue)
            ->WithWhiteListTargetIds(WhiteListTargetIdsValue);
    }

    TSharedPtr<FEzDistributorModel> FEzDistributorModel::FromModel(const Gs2::Distributor::Model::FDistributorModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzDistributorModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithInboxNamespaceId(Model->GetInboxNamespaceId())
            ->WithWhiteListTargetIds(Model->GetWhiteListTargetIds());
    }
}