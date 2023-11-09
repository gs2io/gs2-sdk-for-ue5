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

#include "Gs2KeyKey.generated.h"

USTRUCT(BlueprintType)
struct FGs2KeyKey
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString NamespaceName;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString KeyName;
};

UCLASS()
class BPGS2_API UGs2KeyKeyFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};
