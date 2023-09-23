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
#include "Account/Model/BanStatus.h"

namespace Gs2::UE5::Account::Model
{
	class EZGS2_API FEzBanStatus final : public TSharedFromThis<FEzBanStatus>
	{
        TOptional<FString> NameValue;
        TOptional<FString> ReasonValue;
        TOptional<int64> ReleaseTimestampValue;

	public:
        TSharedPtr<FEzBanStatus> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzBanStatus> WithReason(const TOptional<FString> Reason);
        TSharedPtr<FEzBanStatus> WithReleaseTimestamp(const TOptional<int64> ReleaseTimestamp);

        TOptional<FString> GetName() const;

        TOptional<FString> GetReason() const;

        TOptional<int64> GetReleaseTimestamp() const;
        FString GetReleaseTimestampString() const;

        Gs2::Account::Model::FBanStatusPtr ToModel() const;
        static TSharedPtr<FEzBanStatus> FromModel(Gs2::Account::Model::FBanStatusPtr Model);
    };
    typedef TSharedPtr<FEzBanStatus> FEzBanStatusPtr;
}