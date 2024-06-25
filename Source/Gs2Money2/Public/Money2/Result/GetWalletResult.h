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
#include "../Model/Wallet.h"

namespace Gs2::Money2::Result
{
    class GS2MONEY2_API FGetWalletResult final : public TSharedFromThis<FGetWalletResult>
    {
        TSharedPtr<Model::FWallet> ItemValue;
        
    public:
        
        FGetWalletResult();
        FGetWalletResult(
            const FGetWalletResult& From
        );
        ~FGetWalletResult() = default;

        TSharedPtr<FGetWalletResult> WithItem(const TSharedPtr<Model::FWallet> Item);

        TSharedPtr<Model::FWallet> GetItem() const;

        static TSharedPtr<FGetWalletResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetWalletResult, ESPMode::ThreadSafe> FGetWalletResultPtr;
}