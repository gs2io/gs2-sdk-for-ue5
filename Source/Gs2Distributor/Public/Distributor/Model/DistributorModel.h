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
#include "Core/Gs2Object.h"

namespace Gs2::Distributor::Model
{
    class GS2DISTRIBUTOR_API FDistributorModel final : public Gs2Object, public TSharedFromThis<FDistributorModel>
    {
        TOptional<FString> DistributorModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> InboxNamespaceIdValue;
        TSharedPtr<TArray<FString>> WhiteListTargetIdsValue;

    public:
        FDistributorModel();
        FDistributorModel(
            const FDistributorModel& From
        );
        virtual ~FDistributorModel() override = default;

        TSharedPtr<FDistributorModel> WithDistributorModelId(const TOptional<FString> DistributorModelId);
        TSharedPtr<FDistributorModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FDistributorModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FDistributorModel> WithInboxNamespaceId(const TOptional<FString> InboxNamespaceId);
        TSharedPtr<FDistributorModel> WithWhiteListTargetIds(const TSharedPtr<TArray<FString>> WhiteListTargetIds);

        TOptional<FString> GetDistributorModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetInboxNamespaceId() const;
        TSharedPtr<TArray<FString>> GetWhiteListTargetIds() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetDistributorNameFromGrn(const FString Grn);

        static TSharedPtr<FDistributorModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FDistributorModel, ESPMode::ThreadSafe> FDistributorModelPtr;
}