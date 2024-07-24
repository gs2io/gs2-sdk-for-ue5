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

namespace Gs2::Guild::Model
{
    class GS2GUILD_API FLastGuildMasterActivity final : public Gs2Object, public TSharedFromThis<FLastGuildMasterActivity>
    {
        TOptional<FString> UserIdValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FLastGuildMasterActivity();
        FLastGuildMasterActivity(
            const FLastGuildMasterActivity& From
        );
        virtual ~FLastGuildMasterActivity() override = default;

        TSharedPtr<FLastGuildMasterActivity> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FLastGuildMasterActivity> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetUserId() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetGuildModelNameFromGrn(const FString Grn);
        static TOptional<FString> GetGuildNameFromGrn(const FString Grn);

        static TSharedPtr<FLastGuildMasterActivity> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FLastGuildMasterActivity, ESPMode::ThreadSafe> FLastGuildMasterActivityPtr;
}