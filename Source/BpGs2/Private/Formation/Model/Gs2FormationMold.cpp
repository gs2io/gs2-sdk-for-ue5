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

#include "BpGs2/Public/Formation/Model/Gs2FormationMold.h"
#include "BpGs2/Public/Formation/Model/Gs2FormationForm.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Formation/Model/Gs2FormationForm.h"
#include "Core/BpGs2Constant.h"

FGs2FormationOwnForm UGs2FormationMoldFunctionLibrary::OwnForm(
    FGs2FormationOwnMold Mold,
    int32 Index
)
{
    FGs2FormationOwnForm Return;
    if (Mold.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationMoldFunctionLibrary::OwnForm] Mold parameter specification is missing."))
        return Return;
    }
    Return.Value = Mold.Value->Form(
        Index
    );
    return Return;
}