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

#include "Showcase/Model/Gs2ShowcaseRandomShowcase.h"
#include "Showcase/Domain/EzGs2Showcase.h"
#include "Showcase/Model/Gs2ShowcaseRandomDisplayItem.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Showcase/Model/Gs2ShowcaseRandomDisplayItem.h"
#include "Core/BpGs2Constant.h"

FGs2ShowcaseOwnRandomDisplayItem UGs2ShowcaseRandomShowcaseFunctionLibrary::OwnRandomDisplayItem(
    FGs2ShowcaseOwnRandomShowcase RandomShowcase,
    FString DisplayItemName
)
{
    FGs2ShowcaseOwnRandomDisplayItem Return;
    if (RandomShowcase.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ShowcaseRandomShowcaseFunctionLibrary::OwnRandomDisplayItem] RandomShowcase parameter specification is missing."))
        return Return;
    }
    if (DisplayItemName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ShowcaseRandomShowcaseFunctionLibrary::OwnRandomDisplayItem] DisplayItemName parameter specification is missing."))
        return Return;
    }
    Return.Value = RandomShowcase.Value->RandomDisplayItem(
        DisplayItemName
    );
    return Return;
}