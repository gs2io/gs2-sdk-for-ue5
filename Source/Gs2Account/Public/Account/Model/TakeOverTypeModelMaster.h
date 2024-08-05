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
#include "OpenIdConnectSetting.h"

namespace Gs2::Account::Model
{
    class GS2ACCOUNT_API FTakeOverTypeModelMaster final : public Gs2Object, public TSharedFromThis<FTakeOverTypeModelMaster>
    {
        TOptional<FString> TakeOverTypeModelIdValue;
        TOptional<int32> TypeValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<FOpenIdConnectSetting> OpenIdConnectSettingValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FTakeOverTypeModelMaster();
        FTakeOverTypeModelMaster(
            const FTakeOverTypeModelMaster& From
        );
        virtual ~FTakeOverTypeModelMaster() override = default;

        TSharedPtr<FTakeOverTypeModelMaster> WithTakeOverTypeModelId(const TOptional<FString> TakeOverTypeModelId);
        TSharedPtr<FTakeOverTypeModelMaster> WithType(const TOptional<int32> Type);
        TSharedPtr<FTakeOverTypeModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FTakeOverTypeModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FTakeOverTypeModelMaster> WithOpenIdConnectSetting(const TSharedPtr<FOpenIdConnectSetting> OpenIdConnectSetting);
        TSharedPtr<FTakeOverTypeModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FTakeOverTypeModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FTakeOverTypeModelMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetTakeOverTypeModelId() const;
        TOptional<int32> GetType() const;
        FString GetTypeString() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<FOpenIdConnectSetting> GetOpenIdConnectSetting() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetTypeFromGrn(const FString Grn);

        static TSharedPtr<FTakeOverTypeModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FTakeOverTypeModelMaster, ESPMode::ThreadSafe> FTakeOverTypeModelMasterPtr;
}