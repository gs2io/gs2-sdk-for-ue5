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
#include "Formation/Model/Mold.h"

namespace Gs2::UE5::Formation::Model
{
	class EZGS2_API FEzMold final : public TSharedFromThis<FEzMold>
	{
        TOptional<FString> NameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> CapacityValue;

	public:
        TSharedPtr<FEzMold> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzMold> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzMold> WithCapacity(const TOptional<int32> Capacity);

        TOptional<FString> GetName() const;

        TOptional<FString> GetUserId() const;

        TOptional<int32> GetCapacity() const;
        FString GetCapacityString() const;

        Gs2::Formation::Model::FMoldPtr ToModel() const;
        static TSharedPtr<FEzMold> FromModel(Gs2::Formation::Model::FMoldPtr Model);
    };
    typedef TSharedPtr<FEzMold> FEzMoldPtr;
}