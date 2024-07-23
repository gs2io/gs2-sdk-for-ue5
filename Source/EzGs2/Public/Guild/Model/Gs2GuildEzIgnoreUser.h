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
#include "Guild/Model/IgnoreUser.h"

namespace Gs2::UE5::Guild::Model
{
	class EZGS2_API FEzIgnoreUser final : public TSharedFromThis<FEzIgnoreUser>
	{
        TOptional<FString> UserIdValue;

	public:
        TSharedPtr<FEzIgnoreUser> WithUserId(const TOptional<FString> UserId);

        TOptional<FString> GetUserId() const;

        Gs2::Guild::Model::FIgnoreUserPtr ToModel() const;
        static TSharedPtr<FEzIgnoreUser> FromModel(Gs2::Guild::Model::FIgnoreUserPtr Model);
    };
    typedef TSharedPtr<FEzIgnoreUser> FEzIgnoreUserPtr;
}