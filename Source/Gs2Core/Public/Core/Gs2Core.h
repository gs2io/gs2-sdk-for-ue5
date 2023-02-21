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

#include "Model/BasicGs2Credential.h"
#include "Model/Gs2Credential.h"
#include "Model/Gs2Error.h"
#include "Model/Region.h"
#include "Net/Rest/Task/RestCloseTask.h"
#include "Net/Rest/Task/RestOpenTask.h"
#include "Net/Rest/Gs2RestSession.h"
#include "Net/Result/CloseTaskResult.h"
#include "Net/Result/OpenTaskResult.h"
#include "Net/Task/CloseTask.h"
#include "Net/Task/OpenTask.h"
#include "Net/WebSocket/Task/WebSocketCloseTask.h"
#include "Net/WebSocket/Task/WebSocketOpenTask.h"
#include "Net/WebSocket/Task/WebSocketResult.h"
#include "Net/WebSocket/Task/WebSocketSessionRequest.h"
#include "Net/AbstractGs2Client.h"
#include "Net/AbstractWebSocketGs2Client.h"
#include "Net/Gs2Session.h"
#include "Util/Gs2Future.h"
#include "Gs2Constant.h"