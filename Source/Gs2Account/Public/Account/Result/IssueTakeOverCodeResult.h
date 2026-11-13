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
#include "../Model/TakeOver.h"

namespace Gs2::Account::Result
{
    class GS2ACCOUNT_API FIssueTakeOverCodeResult final : public TSharedFromThis<FIssueTakeOverCodeResult>
    {
        TSharedPtr<Model::FTakeOver> ItemValue;
        TOptional<FString> PasswordValue;
        
    public:
        
        FIssueTakeOverCodeResult();
        FIssueTakeOverCodeResult(
            const FIssueTakeOverCodeResult& From
        );
        ~FIssueTakeOverCodeResult() = default;

        TSharedPtr<FIssueTakeOverCodeResult> WithItem(const TSharedPtr<Model::FTakeOver> Item);
        TSharedPtr<FIssueTakeOverCodeResult> WithPassword(const TOptional<FString> Password);

        TSharedPtr<Model::FTakeOver> GetItem() const;
        TOptional<FString> GetPassword() const;

        static TSharedPtr<FIssueTakeOverCodeResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FIssueTakeOverCodeResult, ESPMode::ThreadSafe> FIssueTakeOverCodeResultPtr;
}