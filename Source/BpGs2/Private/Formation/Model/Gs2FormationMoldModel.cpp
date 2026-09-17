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

#include "Formation/Model/Gs2FormationMoldModel.h"
#include "Formation/Domain/EzGs2Formation.h"
#include "Formation/Model/Gs2FormationFormModel.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Formation/Model/Gs2FormationFormModel.h"
#include "Core/BpGs2Constant.h"

FGs2FormationFormModel UGs2FormationMoldModelFunctionLibrary::FormModel(
    FGs2FormationMoldModel MoldModel
)
{
    FGs2FormationFormModel Return;
    if (MoldModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationMoldModelFunctionLibrary::FormModel] MoldModel parameter specification is missing."))
        return Return;
    }
    Return.Value = MoldModel.Value->FormModel(
    );
    return Return;
}