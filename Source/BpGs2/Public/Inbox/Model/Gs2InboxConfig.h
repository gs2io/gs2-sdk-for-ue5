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

#include "Inbox/Model/Gs2InboxEzConfig.h"
#include "Gs2InboxConfig.generated.h"

USTRUCT(BlueprintType)
struct FGs2InboxConfig
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString Key = "";
    UPROPERTY(BlueprintReadWrite)
    FString Value = "";
};

inline FGs2InboxConfig EzConfigToFGs2InboxConfig(
    const Gs2::UE5::Inbox::Model::FEzConfigPtr Model
)
{
    FGs2InboxConfig Value;
    Value.Key = Model->GetKey() ? *Model->GetKey() : "";
    Value.Value = Model->GetValue() ? *Model->GetValue() : "";
    return Value;
}

inline Gs2::UE5::Inbox::Model::FEzConfigPtr FGs2InboxConfigToEzConfig(
    const FGs2InboxConfig Model
)
{
    return MakeShared<Gs2::UE5::Inbox::Model::FEzConfig>()
        ->WithKey(Model.Key)
        ->WithValue(Model.Value);
}