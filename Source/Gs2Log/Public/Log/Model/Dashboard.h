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

namespace Gs2::Log::Model
{
    class GS2LOG_API FDashboard final : public FGs2Object, public TSharedFromThis<FDashboard>
    {
        TOptional<FString> DashboardIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DisplayNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> PayloadValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FDashboard();
        FDashboard(
            const FDashboard& From
        );
        virtual ~FDashboard() override = default;

        TSharedPtr<FDashboard> WithDashboardId(const TOptional<FString> DashboardId);
        TSharedPtr<FDashboard> WithName(const TOptional<FString> Name);
        TSharedPtr<FDashboard> WithDisplayName(const TOptional<FString> DisplayName);
        TSharedPtr<FDashboard> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FDashboard> WithPayload(const TOptional<FString> Payload);
        TSharedPtr<FDashboard> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FDashboard> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetDashboardId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDisplayName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetPayload() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetDashboardNameFromGrn(const FString Grn);

        static TSharedPtr<FDashboard> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FDashboard, ESPMode::ThreadSafe> FDashboardPtr;
}