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

namespace Gs2::SeasonRating::Model
{
    class GS2SEASONRATING_API FCurrentSeasonModelMaster final : public Gs2Object, public TSharedFromThis<FCurrentSeasonModelMaster>
    {
        TOptional<FString> NamespaceIdValue;
        TOptional<FString> SettingsValue;

    public:
        FCurrentSeasonModelMaster();
        FCurrentSeasonModelMaster(
            const FCurrentSeasonModelMaster& From
        );
        virtual ~FCurrentSeasonModelMaster() override = default;

        TSharedPtr<FCurrentSeasonModelMaster> WithNamespaceId(const TOptional<FString> NamespaceId);
        TSharedPtr<FCurrentSeasonModelMaster> WithSettings(const TOptional<FString> Settings);

        TOptional<FString> GetNamespaceId() const;
        TOptional<FString> GetSettings() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);

        static TSharedPtr<FCurrentSeasonModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FCurrentSeasonModelMaster, ESPMode::ThreadSafe> FCurrentSeasonModelMasterPtr;
}