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
#include "Distributor/Model/DistributeResource.h"

namespace Gs2::UE5::Distributor::Model
{
	class EZGS2_API FEzDistributeResource final : public TSharedFromThis<FEzDistributeResource>
	{
        TOptional<FString> ActionValue;
        TOptional<FString> RequestValue;

	public:
        TSharedPtr<FEzDistributeResource> WithAction(const TOptional<FString> Action);
        TSharedPtr<FEzDistributeResource> WithRequest(const TOptional<FString> Request);

        TOptional<FString> GetAction() const;

        TOptional<FString> GetRequest() const;

        Gs2::Distributor::Model::FDistributeResourcePtr ToModel() const;
        static TSharedPtr<FEzDistributeResource> FromModel(Gs2::Distributor::Model::FDistributeResourcePtr Model);
    };
    typedef TSharedPtr<FEzDistributeResource> FEzDistributeResourcePtr;
}