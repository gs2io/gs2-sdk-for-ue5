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
    class GS2ACCOUNT_API FTakeOverTypeModel final : public Gs2Object, public TSharedFromThis<FTakeOverTypeModel>
    {
        TOptional<FString> TakeOverTypeModelIdValue;
        TOptional<int32> TypeValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<FOpenIdConnectSetting> OpenIdConnectSettingValue;

    public:
        FTakeOverTypeModel();
        FTakeOverTypeModel(
            const FTakeOverTypeModel& From
        );
        virtual ~FTakeOverTypeModel() override = default;

        TSharedPtr<FTakeOverTypeModel> WithTakeOverTypeModelId(const TOptional<FString> TakeOverTypeModelId);
        TSharedPtr<FTakeOverTypeModel> WithType(const TOptional<int32> Type);
        TSharedPtr<FTakeOverTypeModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FTakeOverTypeModel> WithOpenIdConnectSetting(const TSharedPtr<FOpenIdConnectSetting> OpenIdConnectSetting);

        TOptional<FString> GetTakeOverTypeModelId() const;
        TOptional<int32> GetType() const;
        FString GetTypeString() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<FOpenIdConnectSetting> GetOpenIdConnectSetting() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetTypeFromGrn(const FString Grn);

        static TSharedPtr<FTakeOverTypeModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FTakeOverTypeModel, ESPMode::ThreadSafe> FTakeOverTypeModelPtr;
}