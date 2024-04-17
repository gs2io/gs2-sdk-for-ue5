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
#include "Buff/Model/BuffTargetGrn.h"

namespace Gs2::UE5::Buff::Model
{
	class EZGS2_API FEzBuffTargetGrn final : public TSharedFromThis<FEzBuffTargetGrn>
	{
        TOptional<FString> TargetModelNameValue;
        TOptional<FString> TargetGrnValue;

	public:
        TSharedPtr<FEzBuffTargetGrn> WithTargetModelName(const TOptional<FString> TargetModelName);
        TSharedPtr<FEzBuffTargetGrn> WithTargetGrn(const TOptional<FString> TargetGrn);

        TOptional<FString> GetTargetModelName() const;

        TOptional<FString> GetTargetGrn() const;

        Gs2::Buff::Model::FBuffTargetGrnPtr ToModel() const;
        static TSharedPtr<FEzBuffTargetGrn> FromModel(Gs2::Buff::Model::FBuffTargetGrnPtr Model);
    };
    typedef TSharedPtr<FEzBuffTargetGrn> FEzBuffTargetGrnPtr;
}