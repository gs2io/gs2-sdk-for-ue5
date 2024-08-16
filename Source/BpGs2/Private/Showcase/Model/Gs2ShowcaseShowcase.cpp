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

#include "Showcase/Model/Gs2ShowcaseShowcase.h"
#include "Showcase/Domain/EzGs2Showcase.h"
#include "Showcase/Model/Gs2ShowcaseDisplayItem.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Showcase/Model/Gs2ShowcaseDisplayItem.h"
#include "Core/BpGs2Constant.h"

FGs2ShowcaseOwnDisplayItem UGs2ShowcaseShowcaseFunctionLibrary::OwnDisplayItem(
    FGs2ShowcaseOwnShowcase Showcase,
    FString DisplayItemId
)
{
    FGs2ShowcaseOwnDisplayItem Return;
    if (Showcase.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ShowcaseShowcaseFunctionLibrary::OwnDisplayItem] Showcase parameter specification is missing."))
        return Return;
    }
    if (DisplayItemId == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ShowcaseShowcaseFunctionLibrary::OwnDisplayItem] DisplayItemId parameter specification is missing."))
        return Return;
    }
    Return.Value = Showcase.Value->DisplayItem(
        DisplayItemId
    );
    return Return;
}