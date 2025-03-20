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
#include "Core/Gs2Object.h"
#include "AcquireAction.h"

namespace Gs2::Idle::Model
{
    class GS2IDLE_API FAcquireActionList final : public FGs2Object, public TSharedFromThis<FAcquireActionList>
    {
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> AcquireActionsValue;

    public:
        FAcquireActionList();
        FAcquireActionList(
            const FAcquireActionList& From
        );
        virtual ~FAcquireActionList() override = default;

        TSharedPtr<FAcquireActionList> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> AcquireActions);

        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> GetAcquireActions() const;


        static TSharedPtr<FAcquireActionList> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FAcquireActionList, ESPMode::ThreadSafe> FAcquireActionListPtr;
}