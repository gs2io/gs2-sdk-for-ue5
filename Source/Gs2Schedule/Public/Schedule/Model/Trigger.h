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

namespace Gs2::Schedule::Model
{
    class GS2SCHEDULE_API FTrigger final : public TSharedFromThis<FTrigger>
    {
        TOptional<FString> TriggerIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> ExpiresAtValue;

    public:
        FTrigger();
        FTrigger(
            const FTrigger& From
        );
        ~FTrigger() = default;

        TSharedPtr<FTrigger> WithTriggerId(const TOptional<FString> TriggerId);
        TSharedPtr<FTrigger> WithName(const TOptional<FString> Name);
        TSharedPtr<FTrigger> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FTrigger> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FTrigger> WithExpiresAt(const TOptional<int64> ExpiresAt);

        TOptional<FString> GetTriggerId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetExpiresAt() const;
        FString GetExpiresAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetTriggerNameFromGrn(const FString Grn);

        static TSharedPtr<FTrigger> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FTrigger, ESPMode::ThreadSafe> FTriggerPtr;
}