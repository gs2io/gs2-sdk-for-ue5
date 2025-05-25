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

// Model
#include "Model/AccessToken.h"

// Login
#include "Request/LoginRequest.h"
#include "Result/LoginResult.h"
#include "Task/Rest/LoginTask.h"
#include "Task/WebSocket/LoginTask.h"

// LoginBySignature
#include "Request/LoginBySignatureRequest.h"
#include "Result/LoginBySignatureResult.h"
#include "Task/Rest/LoginBySignatureTask.h"
#include "Task/WebSocket/LoginBySignatureTask.h"

// Federation
#include "Request/FederationRequest.h"
#include "Result/FederationResult.h"
#include "Task/Rest/FederationTask.h"
#include "Task/WebSocket/FederationTask.h"

// IssueTimeOffsetTokenByUserId
#include "Request/IssueTimeOffsetTokenByUserIdRequest.h"
#include "Result/IssueTimeOffsetTokenByUserIdResult.h"
#include "Task/Rest/IssueTimeOffsetTokenByUserIdTask.h"
#include "Task/WebSocket/IssueTimeOffsetTokenByUserIdTask.h"

// GetServiceVersion
#include "Request/GetServiceVersionRequest.h"
#include "Result/GetServiceVersionResult.h"
#include "Task/Rest/GetServiceVersionTask.h"
#include "Task/WebSocket/GetServiceVersionTask.h"

// Client
#include "Gs2AuthRestClient.h"
#include "Gs2AuthWebSocketClient.h"