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

namespace Gs2::Account::Model
{
    class GS2ACCOUNT_API FBanStatus final : public Gs2Object, public TSharedFromThis<FBanStatus>
    {
        TOptional<FString> NameValue;
        TOptional<FString> ReasonValue;
        TOptional<int64> ReleaseTimestampValue;

    public:
        FBanStatus();
        FBanStatus(
            const FBanStatus& From
        );
        virtual ~FBanStatus() override = default;

        TSharedPtr<FBanStatus> WithName(const TOptional<FString> Name);
        TSharedPtr<FBanStatus> WithReason(const TOptional<FString> Reason);
        TSharedPtr<FBanStatus> WithReleaseTimestamp(const TOptional<int64> ReleaseTimestamp);

        TOptional<FString> GetName() const;
        TOptional<FString> GetReason() const;
        TOptional<int64> GetReleaseTimestamp() const;
        FString GetReleaseTimestampString() const;


        static TSharedPtr<FBanStatus> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FBanStatus, ESPMode::ThreadSafe> FBanStatusPtr;
}