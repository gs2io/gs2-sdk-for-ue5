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

namespace Gs2::Version::Model
{
    class GS2VERSION_API FCurrentVersionMaster final : public FGs2Object, public TSharedFromThis<FCurrentVersionMaster>
    {
        TOptional<FString> NamespaceIdValue;
        TOptional<FString> SettingsValue;

    public:
        FCurrentVersionMaster();
        FCurrentVersionMaster(
            const FCurrentVersionMaster& From
        );
        virtual ~FCurrentVersionMaster() override = default;

        TSharedPtr<FCurrentVersionMaster> WithNamespaceId(const TOptional<FString> NamespaceId);
        TSharedPtr<FCurrentVersionMaster> WithSettings(const TOptional<FString> Settings);

        TOptional<FString> GetNamespaceId() const;
        TOptional<FString> GetSettings() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);

        static TSharedPtr<FCurrentVersionMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FCurrentVersionMaster, ESPMode::ThreadSafe> FCurrentVersionMasterPtr;
}