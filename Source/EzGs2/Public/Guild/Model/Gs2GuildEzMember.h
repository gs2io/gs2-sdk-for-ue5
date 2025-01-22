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
#include "Guild/Model/Member.h"

namespace Gs2::UE5::Guild::Model
{
	class EZGS2_API FEzMember final : public TSharedFromThis<FEzMember>
	{
        TOptional<FString> UserIdValue;
        TOptional<FString> RoleNameValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> JoinedAtValue;

	public:
        TSharedPtr<FEzMember> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzMember> WithRoleName(const TOptional<FString> RoleName);
        TSharedPtr<FEzMember> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzMember> WithJoinedAt(const TOptional<int64> JoinedAt);

        TOptional<FString> GetUserId() const;

        TOptional<FString> GetRoleName() const;

        TOptional<FString> GetMetadata() const;

        TOptional<int64> GetJoinedAt() const;
        FString GetJoinedAtString() const;

        Gs2::Guild::Model::FMemberPtr ToModel() const;
        static TSharedPtr<FEzMember> FromModel(Gs2::Guild::Model::FMemberPtr Model);
    };
    typedef TSharedPtr<FEzMember> FEzMemberPtr;
}