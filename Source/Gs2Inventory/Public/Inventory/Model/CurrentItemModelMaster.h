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

namespace Gs2::Inventory::Model
{
    class GS2INVENTORY_API FCurrentItemModelMaster final : public TSharedFromThis<FCurrentItemModelMaster>
    {
        TOptional<FString> NamespaceIdValue;
        TOptional<FString> SettingsValue;

    public:
        FCurrentItemModelMaster();
        FCurrentItemModelMaster(
            const FCurrentItemModelMaster& From
        );
        ~FCurrentItemModelMaster() = default;

        TSharedPtr<FCurrentItemModelMaster> WithNamespaceId(const TOptional<FString> NamespaceId);
        TSharedPtr<FCurrentItemModelMaster> WithSettings(const TOptional<FString> Settings);

        TOptional<FString> GetNamespaceId() const;
        TOptional<FString> GetSettings() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);

        static TSharedPtr<FCurrentItemModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FCurrentItemModelMaster, ESPMode::ThreadSafe> FCurrentItemModelMasterPtr;
}