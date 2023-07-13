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

namespace Gs2::LoginReward::Model
{
    class GS2LOGINREWARD_API FReceiveStatus final : public Gs2Object, public TSharedFromThis<FReceiveStatus>
    {
        TOptional<FString> ReceiveStatusIdValue;
        TOptional<FString> BonusModelNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<bool>> ReceivedStepsValue;
        TOptional<int64> LastReceivedAtValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FReceiveStatus();
        FReceiveStatus(
            const FReceiveStatus& From
        );
        virtual ~FReceiveStatus() override = default;

        TSharedPtr<FReceiveStatus> WithReceiveStatusId(const TOptional<FString> ReceiveStatusId);
        TSharedPtr<FReceiveStatus> WithBonusModelName(const TOptional<FString> BonusModelName);
        TSharedPtr<FReceiveStatus> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FReceiveStatus> WithReceivedSteps(const TSharedPtr<TArray<bool>> ReceivedSteps);
        TSharedPtr<FReceiveStatus> WithLastReceivedAt(const TOptional<int64> LastReceivedAt);
        TSharedPtr<FReceiveStatus> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FReceiveStatus> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetReceiveStatusId() const;
        TOptional<FString> GetBonusModelName() const;
        TOptional<FString> GetUserId() const;
        TSharedPtr<TArray<bool>> GetReceivedSteps() const;
        TOptional<int64> GetLastReceivedAt() const;
        FString GetLastReceivedAtString() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetBonusModelNameFromGrn(const FString Grn);

        static TSharedPtr<FReceiveStatus> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FReceiveStatus, ESPMode::ThreadSafe> FReceiveStatusPtr;
}