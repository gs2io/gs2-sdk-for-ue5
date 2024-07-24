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
#include "Guild/Model/LastGuildMasterActivity.h"

namespace Gs2::UE5::Guild::Model
{
	class EZGS2_API FEzLastGuildMasterActivity final : public TSharedFromThis<FEzLastGuildMasterActivity>
	{
        TOptional<FString> UserIdValue;
        TOptional<int64> UpdatedAtValue;

	public:
        TSharedPtr<FEzLastGuildMasterActivity> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzLastGuildMasterActivity> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetUserId() const;

        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        Gs2::Guild::Model::FLastGuildMasterActivityPtr ToModel() const;
        static TSharedPtr<FEzLastGuildMasterActivity> FromModel(Gs2::Guild::Model::FLastGuildMasterActivityPtr Model);
    };
    typedef TSharedPtr<FEzLastGuildMasterActivity> FEzLastGuildMasterActivityPtr;
}