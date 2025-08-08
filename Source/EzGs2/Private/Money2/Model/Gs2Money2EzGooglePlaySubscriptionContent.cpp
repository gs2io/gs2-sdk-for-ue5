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

#include "Money2/Model/Gs2Money2EzGooglePlaySubscriptionContent.h"

namespace Gs2::UE5::Money2::Model
{

    TSharedPtr<FEzGooglePlaySubscriptionContent> FEzGooglePlaySubscriptionContent::WithProductId(
        const TOptional<FString> ProductId
    )
    {
        this->ProductIdValue = ProductId;
        return SharedThis(this);
    }
    TOptional<FString> FEzGooglePlaySubscriptionContent::GetProductId() const
    {
        return ProductIdValue;
    }

    Gs2::Money2::Model::FGooglePlaySubscriptionContentPtr FEzGooglePlaySubscriptionContent::ToModel() const
    {
        return MakeShared<Gs2::Money2::Model::FGooglePlaySubscriptionContent>()
            ->WithProductId(ProductIdValue);
    }

    TSharedPtr<FEzGooglePlaySubscriptionContent> FEzGooglePlaySubscriptionContent::FromModel(const Gs2::Money2::Model::FGooglePlaySubscriptionContentPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzGooglePlaySubscriptionContent>()
            ->WithProductId(Model->GetProductId());
    }
}