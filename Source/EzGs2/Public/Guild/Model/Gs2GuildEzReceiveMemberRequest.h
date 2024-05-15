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
#include "Guild/Model/ReceiveMemberRequest.h"

namespace Gs2::UE5::Guild::Model
{
	class EZGS2_API FEzReceiveMemberRequest final : public TSharedFromThis<FEzReceiveMemberRequest>
	{
        TOptional<FString> UserIdValue;
        TOptional<FString> TargetGuildNameValue;

	public:
        TSharedPtr<FEzReceiveMemberRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzReceiveMemberRequest> WithTargetGuildName(const TOptional<FString> TargetGuildName);

        TOptional<FString> GetUserId() const;

        TOptional<FString> GetTargetGuildName() const;

        Gs2::Guild::Model::FReceiveMemberRequestPtr ToModel() const;
        static TSharedPtr<FEzReceiveMemberRequest> FromModel(Gs2::Guild::Model::FReceiveMemberRequestPtr Model);
    };
    typedef TSharedPtr<FEzReceiveMemberRequest> FEzReceiveMemberRequestPtr;
}