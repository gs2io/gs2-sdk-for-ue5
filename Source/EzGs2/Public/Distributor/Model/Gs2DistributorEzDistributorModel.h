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

#pragma once

#include "CoreMinimal.h"
#include "Distributor/Model/DistributorModel.h"

namespace Gs2::UE5::Distributor::Model
{
	class EZGS2_API FEzDistributorModel final : public TSharedFromThis<FEzDistributorModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> InboxNamespaceIdValue;
        TSharedPtr<TArray<FString>> WhiteListTargetIdsValue;

	public:
        TSharedPtr<FEzDistributorModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzDistributorModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzDistributorModel> WithInboxNamespaceId(const TOptional<FString> InboxNamespaceId);
        TSharedPtr<FEzDistributorModel> WithWhiteListTargetIds(const TSharedPtr<TArray<FString>> WhiteListTargetIds);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TOptional<FString> GetInboxNamespaceId() const;

        TSharedPtr<TArray<FString>> GetWhiteListTargetIds() const;

        Gs2::Distributor::Model::FDistributorModelPtr ToModel() const;
        static TSharedPtr<FEzDistributorModel> FromModel(Gs2::Distributor::Model::FDistributorModelPtr Model);
    };
    typedef TSharedPtr<FEzDistributorModel> FEzDistributorModelPtr;
}